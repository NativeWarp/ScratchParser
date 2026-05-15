#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <scratch/parse.h>
#include <cwalk.h>
#include <stdint.h>
#include <zip.h>
#include <zlib.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <zipconf.h>

#if defined(__unix__)
    #include <sys/stat.h>
    #include <unistd.h>

    static struct stat _sb;

    #define __scratch_homedir() getenv("HOME")
    #define __scratch_mkdir(dir) mkdir(dir, 0755)
    #define __scratch_exists(path) (stat(path, &_sb) == 0)
    #define __scratch_isdir(path) (stat(path, &_sb) == 0 && S_ISDIR(_sb.st_mode))
    #define __scratch_rmdir(dir) rmdir(dir)
#elif defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #define __scratch_homedir() getenv("USERPROFILE")
    #define __scratch_mkdir(dir) CreateDirectory(dir, NULL)
    #define __scratch_exists(path) (GetFileAttributes(dir) != INVALID_FILE_ATTRIBUTES)
    #define __scratch_isdir(path) (GetFileAttributes(dir) & FILE_ATTRIBUTE_DIRECTORY)
    #define __scratch_rmdir(dir) RemoveDirectory(dir)
#else
    #error "Unable to determine system."
#endif

bool scratch_project_load(const char* file_path, size_t* identifier) {
    char temp_buffer[1 << 16];
    FILE* temp_file;
    size_t temp_counter;

    {
        #define extension_buffer temp_buffer
        #define buffer_length temp_counter

        cwk_path_get_extension(file_path, (const char**)&extension_buffer, &buffer_length);

        if (strncmp((const char*)extension_buffer, ".sb3", buffer_length) != 0) {
            fprintf(stderr, "Path is not a valid .sb3 file: '%s'", file_path);
            return false;
        }

        #undef extension_buffer
        #undef buffer_length
    }

    char project_hash_str[FILENAME_MAX];
    {
        #define bytes_read temp_counter
        #define i temp_counter
        #define file_buffer temp_buffer
        #define hash_buffer temp_buffer
        #define project_file temp_file

        EVP_MD_CTX* ctx;
        const EVP_MD* sha256;
        unsigned int hash_length;

        ctx = EVP_MD_CTX_new();
        sha256 = EVP_sha1();
        EVP_DigestInit_ex(ctx, sha256, NULL);

        project_file = fopen(file_path, "rb");
        if (!project_file) {
            fprintf(stderr, "Cannot open file: '%s'", file_path);
            return false;
        }
        while ((bytes_read = fread(file_buffer, sizeof(*file_buffer), sizeof(file_buffer), project_file)) != 0) {
            // TODO - check if fread caused an error before exiting
            EVP_DigestUpdate(ctx, file_buffer, bytes_read);
        }
        EVP_DigestFinal_ex(ctx, (unsigned char*)hash_buffer, &hash_length);

        memcpy(identifier, hash_buffer, sizeof(*identifier));
        for (i = 0; i < sizeof(*identifier); i++) {
            sprintf(project_hash_str + (i * 2), "%02x", (unsigned char)hash_buffer[i]);
        }

        EVP_MD_free((EVP_MD*)sha256);
        EVP_MD_CTX_free(ctx);

        fclose(project_file);
        
        #undef bytes_read
        #undef i
        #undef file_buffer
        #undef hash_buffer
        #undef project_file
    }
    printf("[DEBUG] project_hash_str = '%s'\n", project_hash_str);

    char project_dir[FILENAME_MAX];
    char project_lock[FILENAME_MAX];
    {
        #define cache_dir temp_buffer

        cwk_path_join(
            __scratch_homedir(), ".scratch",
            cache_dir, sizeof(cache_dir)
        );
        cwk_path_join(
            cache_dir, project_hash_str,
            project_dir, sizeof(project_dir)
        );
        __scratch_mkdir(cache_dir);
        __scratch_mkdir(project_dir);

        cwk_path_join(
            project_dir, "success.lock",
            project_lock, sizeof(project_lock)
        );

        #undef cache_dir
    }
    printf("[DEBUG] project_dir = '%s'\n", project_dir);
    printf("[DEBUG] project_lock = '%s'\n", project_lock);

    {
        #define i temp_counter
        #define extracted_file_name temp_buffer
        #define extracted_file temp_file
        #define extracted_file_buffer temp_buffer

        if (!__scratch_exists(project_lock)) {
            printf("Project not cached!\n");

            zip_t* project_archive;
            int err_code;
            size_t entries;
            zip_error_t zip_error;

            #define __SCRATCH_ZIP_HANDLE_ERROR(condition) \
                if (condition) { \
                    zip_error_init_with_code(&zip_error, err_code); \
                    if (project_archive) zip_close(project_archive); \
                    fprintf(stderr, "Encountered LibZip error: %s\n", zip_error_strerror(&zip_error)); \
                    return false; \
                }

            project_archive = zip_open(file_path, ZIP_RDONLY, &err_code);
            __SCRATCH_ZIP_HANDLE_ERROR(err_code != 0);

            entries = (size_t)zip_get_num_entries(project_archive, 0);
            __SCRATCH_ZIP_HANDLE_ERROR(entries < 0);

            zip_stat_t archived_file_stat;
            zip_file_t* archived_file;
            unsigned long file_crc;
            zip_int64_t bytes_read;

            for (i = 0; i < entries; i++) {
                archived_file = zip_fopen_index(project_archive, i, 0);
                __SCRATCH_ZIP_HANDLE_ERROR(!archived_file)

                err_code = zip_stat_index(project_archive, i, 0, &archived_file_stat);
                __SCRATCH_ZIP_HANDLE_ERROR(err_code != 0)

                cwk_path_join(
                    project_dir, archived_file_stat.name,
                    extracted_file_name, sizeof(extracted_file_name)
                );
                extracted_file = fopen(extracted_file_name, "wb");
                if (!extracted_file) {
                    fprintf(stderr, "Could not open file: '%s'\n", extracted_file_name);
                    return false;
                }

                file_crc = crc32(0, Z_NULL, 0);

                while ((bytes_read = zip_fread(archived_file, extracted_file_buffer, sizeof(extracted_file_buffer))) != 0) {
                    __SCRATCH_ZIP_HANDLE_ERROR(bytes_read == -1)

                    fwrite(extracted_file_buffer, sizeof(*extracted_file_buffer), (size_t)bytes_read, extracted_file);
                    file_crc = crc32(file_crc, (const Bytef*)extracted_file_buffer, (uInt)bytes_read);
                }

                if (
                    archived_file_stat.valid & ZIP_STAT_CRC &&
                    archived_file_stat.crc != file_crc
                ) {
                    fprintf(stderr, "Could not validate file checksum: %zu != %u for '%s'\n", file_crc, archived_file_stat.crc, archived_file_stat.name);
                    return false;
                }

                printf("Successfully extracted file: '%s'\n", archived_file_stat.name);

                fclose(extracted_file);
                zip_fclose(archived_file);
            }

            zip_close(project_archive);
        }

        #undef i
        #undef extracted_file_name
        #undef extracted_file
        #undef extracted_file_buffer
    }

    fclose(fopen(project_lock, "wb"));
    return true;
}
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <scratch/parse.h>
#include <cwalk.h>
#include <zip.h>

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
#elif defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    #define __scratch_homedir() getenv("USERPROFILE")
    #define __scratch_mkdir(dir) CreateDirectory(dir, NULL)
    #define __scratch_exists(path) (GetFileAttributes(dir) != INVALID_FILE_ATTRIBUTES)
    #define __scratch_isdir(path) (GetFileAttributes(dir) & FILE_ATTRIBUTE_DIRECTORY)
#else
    #error "Unable to determine system."
#endif


bool scratch_project_load(const char* file_path, size_t* identifier) {
    {
        const char* extension;
        size_t length;
        cwk_path_get_extension(file_path, &extension, &length);

        if (strncmp(extension, ".sb3", length) != 0) {
            return false;
        }
    }

    size_t project_hash;
    char project_hash_str[FILENAME_MAX];
    {
        EVP_MD_CTX* ctx;
        const EVP_MD* sha256;
        char input_buffer[255];
        char temp_hash[FILENAME_MAX];
        unsigned int hash_length;
        int hash_max_length;
        FILE* project_file;
        size_t bytes_read;

        ctx = EVP_MD_CTX_new();
        sha256 = EVP_sha1();
        EVP_DigestInit_ex(ctx, sha256, NULL);

        project_file = fopen(file_path, "rb");
        if (!project_file) return false;
        while ((bytes_read = fread(input_buffer, sizeof(*input_buffer), sizeof(input_buffer), project_file)) != 0) {
            EVP_DigestUpdate(ctx, input_buffer, bytes_read);
        }

        EVP_DigestFinal_ex(ctx, (unsigned char*)temp_hash, &hash_length);
        hash_max_length = hash_length > sizeof(project_hash) ? sizeof(project_hash) : (int)hash_length;

        memcpy(&project_hash, temp_hash, (size_t)hash_max_length);
        for (int i = 0; i < hash_max_length; i++) {
            sprintf(project_hash_str + (i * 2), "%02x", (unsigned char)temp_hash[i]);
        }

        EVP_MD_free((EVP_MD*)sha256);
        EVP_MD_CTX_free(ctx);
        fclose(project_file);
    }

    char project_dir[FILENAME_MAX];
    {
        char cache_dir[FILENAME_MAX];

        cwk_path_join(
            __scratch_homedir(), ".scratch",
            cache_dir, sizeof(cache_dir)
        );
        if (!__scratch_exists(cache_dir) || !__scratch_isdir(cache_dir)) {
            __scratch_mkdir(cache_dir);
        }

        cwk_path_join(
            cache_dir, project_hash_str,
            project_dir, sizeof(project_dir)
        );
        if (!__scratch_exists(project_dir) || !__scratch_isdir(project_dir)) {
            __scratch_mkdir(project_dir);
        }
    }

    {

        char project_json[FILENAME_MAX];
        cwk_path_join(
            project_dir, "project.json",
            project_json, sizeof(project_json)
        );
        
        if (/* !__scratch_exists(project_json) */ 1) {
            printf("Project not cached!\n");

            zip_t* project_archive;
            int err_code;
            long entries;
            zip_error_t zip_error;

            #define __SCRATCH_ZIP_HANDLE_ERROR(condition) \
                if (condition) { \
                    zip_error_init_with_code(&zip_error, err_code); \
                    fprintf(stderr, "Cannot open project file: %s\n", zip_error_strerror(&zip_error)); \
                    if (project_archive) zip_close(project_archive); \
                    return false; \
                }

            project_archive = zip_open(file_path, ZIP_RDONLY, &err_code);
            __SCRATCH_ZIP_HANDLE_ERROR(err_code != 0);

            entries = zip_get_num_entries(project_archive, 0);
            __SCRATCH_ZIP_HANDLE_ERROR(entries < 0);

            zip_stat_t archived_file_stat;
            zip_file_t* archived_file;
            char file_buf[255];
            char project_filename[FILENAME_MAX];
            FILE* project_file;
            zip_int64_t bytes_read;

            for (long i = 0; i < entries; i++) {
                archived_file = zip_fopen_index(project_archive, (zip_uint64_t)i, 0);
                __SCRATCH_ZIP_HANDLE_ERROR(!archived_file)

                err_code = zip_stat_index(project_archive, (zip_uint64_t)i, 0, &archived_file_stat);
                __SCRATCH_ZIP_HANDLE_ERROR(err_code != 0)

                cwk_path_join(
                    project_dir, archived_file_stat.name,
                    project_filename, sizeof(project_filename)
                );
                project_file = fopen(project_filename, "wb");

                printf("Archived File Name:     '%s'\n", archived_file_stat.name);
                printf("Archived File CRC32:    %u\n", archived_file_stat.crc);

                while ((bytes_read = zip_fread(archived_file, file_buf, sizeof(file_buf))) != 0) {
                    __SCRATCH_ZIP_HANDLE_ERROR(bytes_read == -1)
                    fwrite(file_buf, sizeof(*file_buf), (size_t)bytes_read, project_file);
                }

                fclose(project_file);
                zip_fclose(archived_file);
            }

            zip_close(project_archive);
        }
    }

    printf("Project Hash:   '%s'\n", project_hash_str);

    if (identifier) *identifier = project_hash;
    return true;
}
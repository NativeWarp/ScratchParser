include(CPM)

find_package(LIBZIP)
if (NOT LIBZIP_FOUND)
    CPMAddPackage(
        NAME libzip
        VERSION 1.11.4
        GIT_REPOSITORY https://github.com/nih-at/libzip.git
        GIT_TAG v1.11.4
        OPTIONS
            "BUILD_COVERAGE OFF"
            "BUILD_TOOLS OFF"
            "BUILD_REGRESS OFF"
            "BUILD_OSSFUZZ OFF"
            "BUILD_EXAMPLES OFF"
            "BUILD_DOC OFF"
    )
endif()

target_link_libraries(ScratchParser PUBLIC libzip::zip)
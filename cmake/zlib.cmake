include(CPM)

find_package(ZLIB 1.2.4.1)
if (NOT ZLIB_FOUND)
    CPMAddPackage(
        NAME zlib
        VERSION 1.3.2
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.2
        OPTIONS
            "ZLIB_BUILD_TESTING OFF"
            "ZLIB_PREFIX ON"
    )
endif()

target_link_libraries(ScratchParser PUBLIC ZLIB::ZLIB)
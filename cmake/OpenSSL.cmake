include(CPM)

find_package(OpenSSL 3.6.0)
if (NOT OpenSSL_FOUND)
    if (ANDROID)
        set(OpenSSL_CROSS "CROSS ON")
        set(OpenSSL_CROSS_TARGET "CROSS_TARGET mingw")
        set(OpenSSL_CROSS_ANDROID "CROSS_ANDROID ON")
    endif()
    if (APPLE)
        set(OpenSSL_BUILD_OPENSSL "BUILD_OPENSSL ON")
    endif()

    CPMAddPackage(
        NAME OpenSSL
        VERSION 3.6.0
        GIT_REPOSITORY https://github.com/viaduck/openssl-cmake.git
        GIT_TAG 7e0c2c4
        OPTIONS
            "OPENSSL_BUILD_VERSION 3.6.0"
            "${OpenSSL_CROSS}"
            "${OpenSSL_CROSS_TARGET}"
            "${OpenSSL_CROSS_ANDROID}"
            "${OpenSSL_BUILD_OPENSSL}"
    )

    add_library(OpenSSL::SSL ALIAS ssl)
    add_library(OpenSSL::Crypto ALIAS crypto)
endif()

target_link_libraries(ScratchParser PUBLIC OpenSSL::SSL)
target_link_libraries(ScratchParser PUBLIC OpenSSL::Crypto)
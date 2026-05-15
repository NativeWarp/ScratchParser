include(GenerateExportHeader)

cmake_minimum_required(VERSION 3.13..4.3)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    NativeWarp_ScratchParser
    LANGUAGES C
    VERSION 0.0.1
)

option(NativeWarp_ScratchParser_BUILD_TESTS "Whether to build test executables" ON)

# Global Utilities

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Init project

add_library(ScratchParser)
generate_export_header(ScratchParser)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(ScratchParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(NativeWarp::ScratchParser ALIAS ScratchParser)

target_compile_options(ScratchParser PRIVATE
# Ensure base code integrity.
    -Wall
    -Wextra
    -Wpedantic
    -Werror=deprecated
    -Wunreachable-code-aggressive

# Prevent general unintended behaviour.
    -Wcast-align
    -Wpadded
    -Wshadow
    -Wnull-dereference
    -Wimplicit-fallthrough
    -Wpointer-arith
    -Wfloat-equal

# Prevent unintended behaviour involving casting of numeric types.
    -Wconversion
    -Wsign-conversion
    -Wfloat-conversion
    -Wimplicit-int-float-conversion
    -Wdouble-promotion

# Ensure cross-compiler compatibility.
    -Werror=format=2
    -Werror=pragmas
    -Werror=missing-declarations

# Ensure compatibility with C++.
    -Werror=c++-compat
    -Werror=vla
    -Wstrict-prototypes
    -Werror=missing-prototypes
)

if (BUILD_SHARED_LIBS)
    add_compile_options(-fPIC)
endif()

# Configure submodules

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include(zlib)
include(JSON-C)
include(libzip)
include(cwalk)
include(OpenSSL)

# Configure tests

if (NativeWarp_ScratchParser_BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
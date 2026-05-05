include(CPM)

CPMAddPackage(
    NAME JSON-C
    VERSION 0.18
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG json-c-0.18-20240915
    OPTIONS
        "DISABLE_WERROR ON"
        "ENABLE_THREADING ON"
        "ENABLE_RDRAND ON"
        "BUILD_APPS OFF"
)

target_link_libraries(ScratchParser PRIVATE json-c)
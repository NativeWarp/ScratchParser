include(CPM)

CPMAddPackage(
    NAME cwalk
    VERSION 1.2.9
    GIT_REPOSITORY https://github.com/likle/cwalk.git
    GIT_TAG v1.2.9
)

target_link_libraries(ScratchParser PUBLIC cwalk)
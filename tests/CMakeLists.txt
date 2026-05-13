macro(add_test name)
    add_executable("tests_${name}")

    target_sources("tests_${name}" PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}.c
    )

    target_link_libraries("tests_${name}" PUBLIC ScratchParser)
endmacro()

add_test(parse)
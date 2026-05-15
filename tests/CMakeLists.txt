macro(add_test name)
    add_executable("tests_${name}")

    target_sources("tests_${name}" PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/${name}.c
    )

    target_link_libraries("tests_${name}" PUBLIC ScratchParser)
    add_custom_command(TARGET "tests_${name}" POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:tests_${name}>/resources"
    )
endmacro()

add_test(parse)
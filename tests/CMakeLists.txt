function(add_vsearch_test NAME)
    add_executable(${NAME}
        ${NAME}.cpp
        test_utils.cpp
    )

    target_link_libraries(${NAME}
        PRIVATE
            vsearch
    )

    target_include_directories(${NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()

add_vsearch_test(test_distance)
add_vsearch_test(test_argmin)

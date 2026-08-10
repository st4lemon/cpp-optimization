function(add_vsearch_test NAME)
    add_executable(${NAME}
        vsearch/${NAME}.cpp
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

function(add_common_test NAME)
    add_executable(${NAME}
        common/${NAME}.cpp
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
# add_vsearch_test(test_topk)

add_custom_target(tests
    DEPENDS
        test_distance
        test_argmin
        test_topk
)

add_common_test(test_sort8)

add_custom_target(common_tests
    DEPENDS
        test_sort8
)


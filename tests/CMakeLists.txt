add_executable(test_distance
    test_distance.cpp
    test_utils.cpp
)

target_link_libraries(test_distance
    PRIVATE
        vsearch
)

target_include_directories(test_distance
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_test(
    NAME distance
    COMMAND test_distance
)

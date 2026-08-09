find_package(benchmark REQUIRED)

function(add_benchmark NAME)
    add_executable(${NAME}
        ${NAME}.cpp
    )

    target_link_libraries(${NAME}
        PRIVATE
            vsearch
            benchmark::benchmark
    )
endfunction()

add_benchmark(bench_argmin)
add_benchmark(bench_distance)

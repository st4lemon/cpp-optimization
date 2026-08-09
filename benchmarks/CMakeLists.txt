find_package(benchmark REQUIRED)

add_executable(bench_distance
    bench_distance.cpp
)

target_link_libraries(bench_distance
    PRIVATE
        vsearch
        benchmark::benchmark
)
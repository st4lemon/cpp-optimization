cmake_minimum_required(VERSION 3.28)

project(vsearch
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(VSEARCH_BUILD_TESTS "Build tests" ON)
option(VSEARCH_BUILD_BENCHMARKS "Build benchmarks" ON)

set(VSEARCH_BACKEND "scalar" CACHE STRING "Vector distance backend")
set_property(CACHE VSEARCH_BACKEND PROPERTY STRINGS
    scalar
    avx2
)

add_subdirectory(src)

# Public-facing target. Consumers link to this, not to a specific backend.
add_library(vsearch INTERFACE)
target_link_libraries(vsearch INTERFACE vsearch_backend)

if(VSEARCH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(VSEARCH_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
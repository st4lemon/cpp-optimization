add_library(vsearch_backend_scalar STATIC
    distance/scalar.cpp
)

target_include_directories(vsearch_backend_scalar
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(vsearch_backend_scalar
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_library(vsearch_backend_avx2 STATIC
    distance/avx2.cpp
)

target_include_directories(vsearch_backend_avx2
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(vsearch_backend_avx2
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -mavx2
        -mfma
)

add_library(vsearch_backend INTERFACE)

if(VSEARCH_BACKEND STREQUAL "scalar")
    target_link_libraries(vsearch_backend INTERFACE
        vsearch_backend_scalar
    )
elseif(VSEARCH_BACKEND STREQUAL "avx2")
    target_link_libraries(vsearch_backend INTERFACE
        vsearch_backend_avx2
    )
else()
    message(FATAL_ERROR
        "Unknown VSEARCH_BACKEND='${VSEARCH_BACKEND}'. "
        "Choose 'scalar' or 'avx2'."
    )
endif()
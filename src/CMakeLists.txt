set(VSEARCH_BACKENDS
    scalar
    avx2
    avx2-opt
)

set(VSEARCH_BACKEND_SOURCES_scalar
    distance/scalar.cpp
    argmin/scalar.cpp
)

set(VSEARCH_BACKEND_SOURCES_avx2
    distance/avx2.cpp
    argmin/avx2.cpp
)

set(VSEARCH_BACKEND_SOURCES_avx2_opt
    distance/avx2_opt.cpp
)

set(VSEARCH_BACKEND_COMPILE_OPTIONS_scalar "")
set(VSEARCH_BACKEND_COMPILE_OPTIONS_avx2
    -mavx2
    -mfma
)
set(VSEARCH_BACKEND_COMPILE_OPTIONS_avx2_opt
    -mavx2
    -mfma
)

function(vsearch_add_backend backend)
    string(REPLACE "-" "_" backend_id "${backend}")
    set(target "vsearch_backend_${backend_id}")
    set(source_var "VSEARCH_BACKEND_SOURCES_${backend_id}")

    add_library(${target} STATIC ${${source_var}})
    target_include_directories(${target}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
    target_compile_options(${target}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            ${VSEARCH_BACKEND_COMPILE_OPTIONS_${backend_id}}
    )
endfunction()

foreach(backend IN LISTS VSEARCH_BACKENDS)
    vsearch_add_backend(${backend})
endforeach()

add_library(vsearch_backend INTERFACE)

if(VSEARCH_BACKEND IN_LIST VSEARCH_BACKENDS)
    string(REPLACE "-" "_" selected_backend_id "${VSEARCH_BACKEND}")
    target_link_libraries(vsearch_backend INTERFACE
        vsearch_backend_${selected_backend_id}
    )
else()
    message(FATAL_ERROR
        "Unknown VSEARCH_BACKEND='${VSEARCH_BACKEND}'. "
        "Supported backends: ${VSEARCH_BACKENDS}"
    )
endif()
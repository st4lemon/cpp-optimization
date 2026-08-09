#pragma once

#include <cstddef>

namespace vsearch {

float l2_squared(
    const float* a,
    const float* b,
    std::size_t dimension
);

} // vsearch 
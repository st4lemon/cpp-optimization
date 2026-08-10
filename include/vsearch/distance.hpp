#pragma once

#include <cstddef>
#include <vector>

namespace vsearch {

float l2_squared(
    const std::vector<float> &a,
    const std::vector<float> &b,
    std::size_t dimension
);

} // vsearch 
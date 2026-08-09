#pragma once

#include <cstddef>
#include <utility>

namespace vsearch {

std::pair<float, std::size_t> argmin(
    const float* a,
    std::size_t n
);

} // vsearch 
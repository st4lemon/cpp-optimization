#pragma once

#include <cstddef>
#include <vector>
#include <utility>

namespace vsearch {

// returns a vector containing the smallest k values, 
// formatted as {value, index} unsorted

std::vector<std::pair<float, std::size_t>> topk(
    std::vector<std::pair<float, std::size_t>> &a,
    std::size_t n, 
    std::size_t k
);

} // vsearch 
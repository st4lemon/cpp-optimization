#include <vsearch/argmin.hpp>

namespace vsearch {

std::pair<float, std::size_t> argmin(
    const float* a,
    std::size_t n
) {

    std::size_t res = 0;
    for(std::size_t i = 1; i<n; i++) {
        if(a[i] < a[res]) res = i;
    }
    return {a[res], res};

}

} // vsearch
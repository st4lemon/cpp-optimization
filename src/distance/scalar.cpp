#include <vsearch/distance.hpp>

namespace vsearch {

float l2_squared(
    const float* a,
    const float* b,
    std::size_t dimension
) {
    // Implementation for scalar L2 squared distance calculation
    float sum = 0.0f;
    for (std::size_t i = 0; i < dimension; ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sum;
}

} // vsearch
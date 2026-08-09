#include "test_utils.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace test {

void assert_fp32_eq(
    const std::string name,
    float expected,
    float actual,
    float tolerance
) {
    float diff = std::abs(expected - actual);

    if (diff > tolerance) {
        std::cerr
            << "FAILED: " << name << '\n'
            << "  expected: " << expected << '\n'
            << "  actual:   " << actual << '\n'
            << "  diff:     " << diff << '\n';
        std::abort();
    }
}

} // namespace test
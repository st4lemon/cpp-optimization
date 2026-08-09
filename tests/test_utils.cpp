#include "test_utils.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#define TEST_FAIL(n, e, a, d) \
    do { \
        std::cerr \
            << "FAILED: " << n << '\n' \
            << "  expected: " << e << '\n' \
            << "  actual:   " << a << '\n' \
            << "  diff:     " << d << '\n'; \
        std::abort(); \
    } while(false); 

namespace test {

void assert_fp32_eq(
    const std::string name,
    float expected,
    float actual,
    float tolerance
) {
    float diff = std::abs(expected - actual);

    if (diff > tolerance) {
        TEST_FAIL(name, expected, actual, diff)
    }
}

void assert_int32_eq(
    const std::string name,
    int32_t expected,
    int32_t actual
) {

    if (expected != actual) {
        TEST_FAIL(name, expected, actual, expected-actual);
    }
}

} // namespace test
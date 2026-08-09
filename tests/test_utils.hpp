#pragma once

#include <string>

namespace test {

void assert_fp32_eq(
    const std::string name,
    float expected,
    float actual,
    float tolerance = 1e-5f
);

} // namespace test


#define ASSERT_FP32_EQ(name, expected, actual) test::assert_fp32_eq(name, expected, actual);
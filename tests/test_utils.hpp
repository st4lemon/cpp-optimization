#pragma once

#include <string>

namespace test {

void assert_fp32_eq(
    const std::string name,
    float expected,
    float actual,
    float tolerance = 1e-5f
);

void assert_int32_eq(
    const std::string name,
    int32_t expected,
    int32_t actual
);

} // namespace test


#define ASSERT_FP32_EQ(name, expected, actual) test::assert_fp32_eq(name, expected, actual);
#define ASSERT_INT32_EQ(name, expected, actual) test::assert_int32_eq(name, expected, actual);
#include "gtest/gtest.h"
#include "adder.h"

TEST(adder, test_eq) {
    adder adder;

    int sum = adder.add(1, 2);
    EXPECT_EQ(sum, 3);
}
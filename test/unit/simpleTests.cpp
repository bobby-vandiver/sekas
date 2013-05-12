#include <iostream>
#include "gtest/gtest.h"
#include "simple.h"

TEST(AddTests, TwoPositiveNumbers) {
	int result = add(2, 10);
	EXPECT_EQ(12, result);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
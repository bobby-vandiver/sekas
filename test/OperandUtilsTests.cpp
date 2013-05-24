#include "gtest/gtest.h"
#include "OperandUtils.h"
#include "IllegalArgumentException.h"

using namespace OperandUtils;

TEST(OperandUtilsTests, IsDataRegisterReturnsTrueForValidDataRegisterLowerCase) {
	EXPECT_TRUE(isDataRegister("d3"));
}

TEST(OperandUtilsTests, IsDataRegisterReturnsTrueForValidDataRegisterUpperCase) {
	EXPECT_TRUE(isDataRegister("D3"));
}

TEST(OperandUtilsTests, IsDataRegisterReturnsTrueForLowerRegisterLimit) {
	EXPECT_TRUE(isDataRegister("d0"));
}

TEST(OperandUtilsTests, IsDataRegisterReturnsTrueForUpperRegisterLimit) {
	EXPECT_TRUE(isDataRegister("d7"));
}

TEST(OperandUtilsTests, IsDataRegisterReturnsFalseForInvalidRegisterNumber) {
	EXPECT_FALSE(isDataRegister("d8"));
}

TEST(OperandUtilsTests, IsDataRegisterReturnsFalseForInvalidRegister) {
	EXPECT_FALSE(isDataRegister("a1"));
}

//=======================================================

TEST(OperandUtilsTests, IsAddressRegisterReturnsTrueForValidAddressRegisterLowerCase) {
	EXPECT_TRUE(isAddressRegister("a3"));
}

TEST(OperandUtilsTests, IsAddressRegisterReturnsTrueForValidAddressRegisterUpperCase) {
	EXPECT_TRUE(isAddressRegister("a3"));
}

TEST(OperandUtilsTests, IsAddressRegisterReturnsTrueForLowerRegisterLimit) {
	EXPECT_TRUE(isAddressRegister("a0"));
}

TEST(OperandUtilsTests, IsAddressRegisterReturnsTrueForUpperRegisterLimit) {
	EXPECT_TRUE(isAddressRegister("a7"));
}

TEST(OperandUtilsTests, IsAddressRegisterReturnsFalseForInvalidRegisterNumber) {
	EXPECT_FALSE(isAddressRegister("a8"));
}

TEST(OperandUtilsTests, IsAddressRegisterReturnsFalseForInvalidRegister) {
	EXPECT_FALSE(isAddressRegister("d1"));
}

//=======================================================

TEST(OperandUtilsTests, IsIndirectRegisterReturnsTrueForValidOperand) {
	EXPECT_TRUE(isIndirectRegister("(a3)"));
}

TEST(OperandUtilsTests, IsIndirectRegisterReturnsFalseForInvalidOperand) {
	EXPECT_FALSE(isIndirectRegister("a3"));
	EXPECT_FALSE(isIndirectRegister("(a3"));
	EXPECT_FALSE(isIndirectRegister("a3)"));
}

//=======================================================

TEST(OperandUtilsTests, IsValidDisplacementMinimumDecimalDisplacement) {
	EXPECT_TRUE(isValidDisplacement("0"));
}

TEST(OperandUtilsTests, IsValidDisplacementMinimumHexadecimalDisplacement) {
	EXPECT_TRUE(isValidDisplacement("$0"));
}

TEST(OperandUtilsTests, IsValidDisplacementEmptyDisplacement) {
	EXPECT_FALSE(isValidDisplacement(""));
}

TEST(OperandUtilsTests, IsValidDisplacementInvalidHexadecimalValue) {
	EXPECT_FALSE(isValidDisplacement("$"));
}

TEST(OperandUtilsTests, IsValidDisplacementDecimalDisplacement) {
	EXPECT_TRUE(isValidDisplacement("12349971"));
}

TEST(OperandUtilsTests, IsValidDisplacementHexadecimalDisplacement) {
	EXPECT_TRUE(isValidDisplacement("$123abC3f"));
}

TEST(OperandUtilsTests, IsValidDisplacementInvalidDisplacement) {
	EXPECT_FALSE(isValidDisplacement("133ga1"));
}
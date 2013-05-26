#include "gtest/gtest.h"
#include "gmock/gmock.h"
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

TEST(OperandUtilsTests, IsIndirectAddressRegisterReturnsTrueForValidOperand) {
	EXPECT_TRUE(isIndirectAddressRegister("(a3)"));
}

TEST(OperandUtilsTests, IsIndirectAddressRegisterReturnsFalseForInvalidOperand) {
	EXPECT_FALSE(isIndirectAddressRegister("a3"));
	EXPECT_FALSE(isIndirectAddressRegister("(a3"));
	EXPECT_FALSE(isIndirectAddressRegister("a3)"));
}

//=======================================================

TEST(OperandUtilsTests, GetRegisterNumberReturnsValidRegisterNumber) {
	EXPECT_EQ(8, getRegisterNumber("B8", 1));
}

TEST(OperandUtilsTests, GetRegisterNumberThrowsExceptionWhenPositionExceedsLength) {
	EXPECT_THROW(getRegisterNumber("a1", 2), IllegalArgumentException);
}

TEST(OperandUtilsTests, GetRegisterNumberThrowsExceptionWhenPositionSpecifiedNotNumber) {
	EXPECT_THROW(getRegisterNumber("d4", 0), IllegalArgumentException);
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

//=======================================================

TEST(OperandUtilsTests, IsValidDisplacementBelowMaxDisplacement) {
	EXPECT_TRUE(isValidDisplacement("1234", 1235));
}

TEST(OperandUtilsTests, IsValidDisplacementMaxDisplacement) {
	EXPECT_TRUE(isValidDisplacement("1234", 1234));
}

TEST(OperandUtilsTests, IsValidDisplacementExceedsMaxDisplacement) {
	EXPECT_FALSE(isValidDisplacement("1234", 1233));
}

//=======================================================

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementDecimalWord) {
	const unsigned int SIZE = WORD_SIZE;
	const unsigned short expectedExtensionWords[SIZE] = {100};
	unsigned short *actualExtensionWords = getExtensionWordsFromDisplacement("100", SIZE);
	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, SIZE));
	delete actualExtensionWords;
}

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementDecimalLong) {
	const unsigned int SIZE = LONG_SIZE;
	const unsigned short expectedExtensionWords[SIZE] = {0xbc, 0x614e};
	unsigned short *actualExtensionWords = getExtensionWordsFromDisplacement("12345678", SIZE);
	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, SIZE));
	delete actualExtensionWords;
}

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementHexadecimalWord) {
	const unsigned int SIZE = WORD_SIZE;
	const unsigned short expectedExtensionWords[SIZE] = {0xfa23};
	unsigned short *actualExtensionWords = getExtensionWordsFromDisplacement("$fa23", SIZE);
	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, SIZE));
	delete actualExtensionWords;
}

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementHexadecimalLong) {
	const unsigned int SIZE = LONG_SIZE;
	const unsigned short expectedExtensionWords[SIZE] = {0xbaad, 0xf00d};
	unsigned short *actualExtensionWords = getExtensionWordsFromDisplacement("$baadf00d", SIZE);
	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, SIZE));
	delete actualExtensionWords;
}

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementThrowsExceptionForInvalidSize) {
	EXPECT_THROW(getExtensionWordsFromDisplacement("100", 3), IllegalArgumentException);
}

TEST(OperandUtilsTests, GetExtensionWordsFromDisplacementRequestWordWithLongDisplacementThrowsException) {
	EXPECT_THROW(getExtensionWordsFromDisplacement("$9ab3f", WORD_SIZE), IllegalArgumentException);
}
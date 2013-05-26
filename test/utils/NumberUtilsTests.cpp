#include "gtest/gtest.h"
#include "NumberUtils.h"
#include "IllegalArgumentException.h"

using namespace NumberUtils;

TEST(NumberUtilsTests, IsValidNumberMinimumDecimalNumber) {
	EXPECT_TRUE(isValidNumber("0"));
}

TEST(NumberUtilsTests, IsValidNumberMinimumHexadecimalNumber) {
	EXPECT_TRUE(isValidNumber("$0"));
}

TEST(NumberUtilsTests, IsValidNumberEmptyNumber) {
	EXPECT_FALSE(isValidNumber(""));
}

TEST(NumberUtilsTests, IsValidNumberInvalidHexadecimalValue) {
	EXPECT_FALSE(isValidNumber("$"));
}

TEST(NumberUtilsTests, IsValidNumberValidDecimalNumber) {
	EXPECT_TRUE(isValidNumber("12349971"));
}

TEST(NumberUtilsTests, IsValidNumberValidHexadecimalNumber) {
	EXPECT_TRUE(isValidNumber("$123abC3f"));
}

TEST(NumberUtilsTests, IsValidNumberInvalidNumber) {
	EXPECT_FALSE(isValidNumber("1faf"));
	EXPECT_FALSE(isValidNumber("$1fga3"));
	EXPECT_FALSE(isValidNumber("133ga1"));
}

//=======================================================

TEST(NumberUtilsTests, ParseNumberThrowsExceptionForInvalidNumber) {
	EXPECT_THROW(parseNumber(""), IllegalArgumentException);
	EXPECT_THROW(parseNumber("$"), IllegalArgumentException);
	EXPECT_THROW(parseNumber("1faf"), IllegalArgumentException);
	EXPECT_THROW(parseNumber("$1fga3"), IllegalArgumentException);
	EXPECT_THROW(parseNumber("133ga1"), IllegalArgumentException);
}

TEST(NumberUtilsTests, ParseNumberParsesDecimal) {
	EXPECT_EQ(1234, parseNumber("1234"));
	EXPECT_EQ(12345678, parseNumber("12345678"));
	EXPECT_EQ(7173402, parseNumber("07173402"));
}

TEST(NumberUtilsTests, ParseNumberParsesHexadecimal) {
	EXPECT_EQ(0x1234, parseNumber("$1234"));
	EXPECT_EQ(0x12345678, parseNumber("$12345678"));
	EXPECT_EQ(0x7173402, parseNumber("$07173402"));
	EXPECT_EQ(0xbaadf00d, parseNumber("$baadf00d"));
	EXPECT_EQ(0x1337cab, parseNumber("$1337CaB"));
}

TEST(NumberUtilsTests, ParseNumberParsesMaxValue) {
	EXPECT_EQ(MAX_NUMBER_ALLOWED, parseNumber("4294967295"));
	EXPECT_EQ(MAX_NUMBER_ALLOWED, parseNumber("$ffffffff"));
	EXPECT_EQ(MAX_NUMBER_ALLOWED, parseNumber("$FFFFFFFF"));
}

// TODO: Need to detect overflow...
// TEST(NumberUtilsTests, ParseNumberThrowsExceptionWhenNumberExceedsMaxValue) {
// 	EXPECT_THROW(parseNumber("4294967296"), IllegalArgumentException);
// 	EXPECT_THROW(parseNumber("$100000000"), IllegalArgumentException);
// }
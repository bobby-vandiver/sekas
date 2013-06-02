#include "gtest/gtest.h"
#include "Symbol.h"
#include "IllegalArgumentException.h"

TEST(SymbolTests, ConstructorThrowsExceptionForInvalidSymbol) {
	EXPECT_THROW(Symbol("1foo"), IllegalArgumentException);
	EXPECT_THROW(Symbol(""), IllegalArgumentException);
	EXPECT_THROW(Symbol("$foo"), IllegalArgumentException);
	EXPECT_THROW(Symbol("#111"), IllegalArgumentException);
	EXPECT_THROW(Symbol("%label"), IllegalArgumentException);
}

TEST(SymbolTests, ConstructorSetsName) {
	Symbol symbol = Symbol("label", 0x1337);
	std::string name = symbol.getName();
	EXPECT_EQ("label", name);
}

TEST(SymbolTests, ConstructorSetsAddress) {
	Symbol symbol = Symbol("label", 0x1337);
	unsigned long address = symbol.getAddress();
	EXPECT_EQ(0x1337, address);
}

TEST(SymbolTests, NameOnlyConstructorSetsName) {
	Symbol symbol = Symbol("label");
	std::string name = symbol.getName();
	EXPECT_EQ("label", name);
}

TEST(SymbolTests, NameOnlyConstructorDefaultsAddressToZero) {
	Symbol symbol = Symbol("label");
	unsigned long address = symbol.getAddress();
	EXPECT_EQ(0, address);
}

TEST(SymbolTests, SetAddress) {
	Symbol symbol = Symbol("label");
	symbol.setAddress(0x1337);
	unsigned long address = symbol.getAddress();
	EXPECT_EQ(0x1337, address);
}

TEST(SymbolTests, IsValidReturnsTrueForValidSymbol) {
	EXPECT_TRUE(Symbol::isValid("somelabel"));
}

TEST(SymbolTests, IsValidReturnsFalseIfSymbolStartsWithDigit) {
	EXPECT_FALSE(Symbol::isValid("1foo"));
}

TEST(SymbolTests, IsValidReturnsFalseIfSymbolIsBlank) {
	EXPECT_FALSE(Symbol::isValid(""));
}

TEST(SymbolTests, IsValidReturnsFalseIfSymbolStartsWithInvalidChar) {
	EXPECT_FALSE(Symbol::isValid("$foo"));
	EXPECT_FALSE(Symbol::isValid("#111"));
	EXPECT_FALSE(Symbol::isValid("%label"));
}
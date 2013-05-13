#include "gtest/gtest.h"
#include "Symbol.h"

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
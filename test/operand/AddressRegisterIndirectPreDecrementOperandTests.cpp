#include "gtest/gtest.h"
#include "AddressRegisterIndirectPreDecrementOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(AddressRegisterIndirectPreDecrementOperandTests, GetExtensionWordCountReturnsZero) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a3)");
	EXPECT_EQ(0, operand->getExtensionWordCount());
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a3)");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, GetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a3)");
	EXPECT_THROW(operand->getExtensionWords(), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a3)");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, GetModeFieldReturns100) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a3)");
	EXPECT_EQ(4, operand->getModeField());
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new AddressRegisterIndirectPreDecrementOperand("-(a4)");
	EXPECT_EQ(4, operand->getRegisterField());
	delete operand;
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, ConstructorValidOperand) {
	EXPECT_NO_THROW(new AddressRegisterIndirectPreDecrementOperand("-(a0)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectPreDecrementOperand("-(a7)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectPreDecrementOperand("-(A5)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("a"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("a33"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("d1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("(a1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("a3))"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("(a5)"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("(a5)+"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPreDecrementOperand("$(a5)"), InvalidOperandException);
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementUpperCase) {
	EXPECT_TRUE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(A1)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementLowerCase) {
	EXPECT_TRUE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(a1)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementLowerRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(a0)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementUpperRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(a7)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementExceedsUpperRegisterLimit) {
	EXPECT_FALSE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(a8)"));
}

TEST(AddressRegisterIndirectPreDecrementOperandTests, IsAddressRegisterIndirectPreDecrementExceedsLength) {
	EXPECT_FALSE(AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement("-(a2))"));
}

#include "gtest/gtest.h"
#include "AddressRegisterIndirectOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(AddressRegisterIndirectOperandTests, GetExtensionWordCountReturnsZero) {
	Operand *operand = new AddressRegisterIndirectOperand("(a3)");
	EXPECT_EQ(0, operand->getExtensionWordCount());
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new AddressRegisterIndirectOperand("(a3)");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, GetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectOperand("(a3)");
	EXPECT_THROW(operand->getExtensionWords(), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectOperand("(a3)");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, GetModeFieldReturns010) {
	Operand *operand = new AddressRegisterIndirectOperand("(a3)");
	EXPECT_EQ(2, operand->getModeField());
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new AddressRegisterIndirectOperand("(a4)");
	EXPECT_EQ(4, operand->getRegisterField());
	delete operand;
}

TEST(AddressRegisterIndirectOperandTests, ConstructorValidOperand) {
	EXPECT_NO_THROW(new AddressRegisterIndirectOperand("(a0)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectOperand("(a7)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectOperand("(A5)"));
}

TEST(AddressRegisterIndirectOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new AddressRegisterIndirectOperand("a"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("a33"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("d1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("(a1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("a3))"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("(a5)+"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectOperand("-(a5)"), InvalidOperandException);
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectUpperCase) {
	EXPECT_TRUE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(A1)"));
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectLowerCase) {
	EXPECT_TRUE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(a1)"));
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectLowerRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(a0)"));
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectUpperRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(a7)"));
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectExceedsUpperRegisterLimit) {
	EXPECT_FALSE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(a8)"));
}

TEST(AddressRegisterIndirectOperandTests, IsAddressRegisterIndirectExceedsLength) {
	EXPECT_FALSE(AddressRegisterIndirectOperand::isAddressRegisterIndirect("(a21)"));
}

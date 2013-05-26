#include "gtest/gtest.h"
#include "AddressRegisterIndirectPostIncrementOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(AddressRegisterIndirectPostIncrementOperandTests, GetExtensionWordCountReturnsZero) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a3)+");
	EXPECT_EQ(0, operand->getExtensionWordCount());
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a3)+");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, GetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a3)+");
	EXPECT_THROW(operand->getExtensionWords(), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a3)+");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, GetModeFieldReturns011) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a3)+");
	EXPECT_EQ(3, operand->getModeField());
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new AddressRegisterIndirectPostIncrementOperand("(a4)+");
	EXPECT_EQ(4, operand->getRegisterField());
	delete operand;
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, ConstructorValidOperand) {
	EXPECT_NO_THROW(new AddressRegisterIndirectPostIncrementOperand("(a0)+"));
	EXPECT_NO_THROW(new AddressRegisterIndirectPostIncrementOperand("(a7)+"));
	EXPECT_NO_THROW(new AddressRegisterIndirectPostIncrementOperand("(A5)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("a"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("a33"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("d1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("(a1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("a3))"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("(a5)"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("-(a5)"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectPostIncrementOperand("(a5)$"), InvalidOperandException);
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementUpperCase) {
	EXPECT_TRUE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(A1)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementLowerCase) {
	EXPECT_TRUE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(a1)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementLowerRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(a0)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementUpperRegisterLimit) {
	EXPECT_TRUE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(a7)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementExceedsUpperRegisterLimit) {
	EXPECT_FALSE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(a8)+"));
}

TEST(AddressRegisterIndirectPostIncrementOperandTests, IsAddressRegisterIndirectPostIncrementExceedsLength) {
	EXPECT_FALSE(AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement("(a21)+"));
}

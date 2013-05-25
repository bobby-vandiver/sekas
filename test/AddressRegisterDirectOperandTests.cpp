#include "gtest/gtest.h"
#include "AddressRegisterDirectOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(AddressRegisterDirectOperandTests, GetExtensionWordCountReturnsZero) {
	Operand *operand = new AddressRegisterDirectOperand("a1");
	EXPECT_EQ(0, operand->getExtensionWordCount());
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new AddressRegisterDirectOperand("a1");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, GetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterDirectOperand("a1");
	EXPECT_THROW(operand->getExtensionWords(), LogicException);
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterDirectOperand("a1");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, GetModeFieldReturns001) {
	Operand *operand = new AddressRegisterDirectOperand("a1");
	EXPECT_EQ(1, operand->getModeField());
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new AddressRegisterDirectOperand("a4");
	EXPECT_EQ(4, operand->getRegisterField());
	delete operand;
}

TEST(AddressRegisterDirectOperandTests, ConstructorValidOperand) {
	EXPECT_NO_THROW(new AddressRegisterDirectOperand("a0"));
	EXPECT_NO_THROW(new AddressRegisterDirectOperand("a7"));
	EXPECT_NO_THROW(new AddressRegisterDirectOperand("A5"));
}

TEST(AddressRegisterDirectOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new AddressRegisterDirectOperand("a"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterDirectOperand("a33"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterDirectOperand("d1"), InvalidOperandException);
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectUpperCase) {
	EXPECT_TRUE(AddressRegisterDirectOperand::isAddressRegisterDirect("A1"));
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectLowerCase) {
	EXPECT_TRUE(AddressRegisterDirectOperand::isAddressRegisterDirect("a1"));
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectLowerRegisterLimit) {
	EXPECT_TRUE(AddressRegisterDirectOperand::isAddressRegisterDirect("a0"));
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectUpperRegisterLimit) {
	EXPECT_TRUE(AddressRegisterDirectOperand::isAddressRegisterDirect("a7"));
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectExceedsUpperRegisterLimit) {
	EXPECT_FALSE(AddressRegisterDirectOperand::isAddressRegisterDirect("a8"));
}

TEST(AddressRegisterDirectOperandTests, IsAddressRegisterDirectExceedsLength) {
	EXPECT_FALSE(AddressRegisterDirectOperand::isAddressRegisterDirect("a21"));
}

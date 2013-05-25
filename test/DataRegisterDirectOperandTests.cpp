#include "gtest/gtest.h"
#include "DataRegisterDirectOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(DataRegisterDirectOperandTests, GetExtensionWordCountReturnsZero) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_EQ(0, operand->getExtensionWordCount());
	delete operand;
}

TEST(DataRegisterDirectOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(DataRegisterDirectOperandTests, GetExtensionWordsThrowsException) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_THROW(operand->getExtensionWords(), LogicException);
	delete operand;
}

TEST(DataRegisterDirectOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(DataRegisterDirectOperandTests, GetModeFieldReturns000) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_EQ(0, operand->getModeField());
	delete operand;
}

TEST(DataRegisterDirectOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new DataRegisterDirectOperand("d1");
	EXPECT_EQ(1, operand->getRegisterField());
	delete operand;
}

TEST(DataRegisterDirectOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new DataRegisterDirectOperand("d8"), InvalidOperandException);
	EXPECT_THROW(new DataRegisterDirectOperand("d"), InvalidOperandException);
	EXPECT_THROW(new DataRegisterDirectOperand("d33"), InvalidOperandException);
	EXPECT_THROW(new DataRegisterDirectOperand("a1"), InvalidOperandException);
}
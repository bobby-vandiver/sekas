#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "AddressRegisterIndirectDisplacementOperand.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

TEST(AddressRegisterIndirectDisplacementOperandTests, GetExtensionWordCountReturnsOne) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(0,a3)");
	EXPECT_EQ(1, operand->getExtensionWordCount());
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, SetExtensionWordCountThrowsException) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(0,a3)");
	EXPECT_THROW(operand->setExtensionWordCount(0), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, GetExtensionWordsReturnsDecimalStandardDisplacement) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(100,a3)");
	ASSERT_EQ(1, operand->getExtensionWordCount());

	const unsigned short expectedExtensionWords[1] = {100};
	unsigned short *actualExtensionWords = operand->getExtensionWords();

	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, 1));
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, GetExtensionWordsReturnsHexadecimalStandardDisplacement) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("($100,a3)");
	ASSERT_EQ(1, operand->getExtensionWordCount());

	const unsigned short expectedExtensionWords[1] = {0x100};
	unsigned short *actualExtensionWords = operand->getExtensionWords();

	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, 1));
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, GetExtensionWordsReturnsDecimalPrefixDisplacement) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("100(a3)");
	ASSERT_EQ(1, operand->getExtensionWordCount());

	const unsigned short expectedExtensionWords[1] = {100};
	unsigned short *actualExtensionWords = operand->getExtensionWords();

	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, 1));
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, GetExtensionWordsReturnsHexadecimalPrefixDisplacement) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("$100(a3)");
	ASSERT_EQ(1, operand->getExtensionWordCount());

	const unsigned short expectedExtensionWords[1] = {0x100};
	unsigned short *actualExtensionWords = operand->getExtensionWords();

	EXPECT_THAT(expectedExtensionWords, ::testing::ElementsAreArray(actualExtensionWords, 1));
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, SetExtensionWordsThrowsException) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(100,a3)");
	EXPECT_THROW(operand->setExtensionWords(NULL), LogicException);
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, GetModeFieldReturns101) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(0,a3)");
	EXPECT_EQ(5, operand->getModeField());
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, ConstructorSetsRegisterField) {
	Operand *operand = new AddressRegisterIndirectDisplacementOperand("(0,a4)");
	EXPECT_EQ(4, operand->getRegisterField());
	delete operand;
}

TEST(AddressRegisterIndirectDisplacementOperandTests, ConstructorValidOperand) {
	EXPECT_NO_THROW(new AddressRegisterIndirectDisplacementOperand("1234(a0)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectDisplacementOperand("$1234(a7)"));
	EXPECT_NO_THROW(new AddressRegisterIndirectDisplacementOperand("$ffff(A5)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, ConstructorSetsRegisterFieldWithInvalidOperand) {
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("a"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("a33"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("d1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("(a1"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("a3))"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("(a5)+"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("-(a5)"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("$(a5)"), InvalidOperandException);
	EXPECT_THROW(new AddressRegisterIndirectDisplacementOperand("$123(a5)+"), InvalidOperandException);
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementMinimumDecimalDisplacement) {
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(0,a1)"));
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("0(a1)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementExceedsUpperRegisterLimit) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(0,a8)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("0(a8)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementInvalidRegister) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(0,d1)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("0(d1)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementInvalidRegisterLength) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(0,a11)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("0(a11)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementMaxDecimalDisplacement) {
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(65535,a1)"));
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("65535(a1)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementExceedsMaxDecimalDisplacement) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(65536,a1)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("65536(a1)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementInvalidDecimalDisplacement) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(123a5,a5)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("123a5(a5)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementMinimumHexadecimalDisplacement) {
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($0,a1)"));
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$0(a1)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementMaxHexadecimalDisplacement) {
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($ffff,a3)"));
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$ffff(a3)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementExceedsMaxHexadecimalDisplacement) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($10000,a3)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$10000(a3)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementInvalidHexadecimalDisplacement) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($aff1ag,a2)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$aff1ag(a2)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementUpperCaseHexadecimal) {
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($f00D,a4)"));
	EXPECT_TRUE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($f00D,a4)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementHexadecimalOnly$) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($,a4)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$(a4)"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementOmitParentheses) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$123,a4)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("$1234(a4"));
}

TEST(AddressRegisterIndirectDisplacementOperandTests, IsAddressRegisterIndirectDisplacementOmitComma) {
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("(1234a4)"));
	EXPECT_FALSE(AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement("($1234a4)"));
}

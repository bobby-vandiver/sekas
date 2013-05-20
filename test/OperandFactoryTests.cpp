#include "gtest/gtest.h"
#include "OperandFactory.h"
#include "OperandTypes.h"

void testOperandReturnsType(std::string operand, std::string expectedType) {
	OperandFactory *operandFactory = OperandFactory::getInstance();
	std::string actualType = operandFactory->getOperandType(operand);
	EXPECT_EQ(expectedType, actualType);
}

//===========================================================
// Data Register Direct
//===========================================================

TEST(OperandFactoryTests, DataDirectOperandUpperCase) {
	testOperandReturnsType("D1", OperandTypes::DataRegisterDirect);
}

TEST(OperandFactoryTests, DataDirectOperandLowerCase) {
	testOperandReturnsType("d1", OperandTypes::DataRegisterDirect);
}

TEST(OperandFactoryTests, DataDirectOperandLowerRegisterLimit) {
	testOperandReturnsType("d0", OperandTypes::DataRegisterDirect);
}

TEST(OperandFactoryTests, DataDirectOperandUpperRegisterLimit) {
	testOperandReturnsType("d7", OperandTypes::DataRegisterDirect);
}

TEST(OperandFactoryTests, DataDirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("d8", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, DataDirectOperandExceedsLength) {
	testOperandReturnsType("d00", OperandTypes::InvalidOperand);
}

//===========================================================
// Address Register Direct
//===========================================================

TEST(OperandFactoryTests, AddressDirectOperandUpperCase) {
	testOperandReturnsType("A1", OperandTypes::AddressRegisterDirect);
}

TEST(OperandFactoryTests, AddressDirectOperandLowerCase) {
	testOperandReturnsType("a1", OperandTypes::AddressRegisterDirect);
}

TEST(OperandFactoryTests, AddressDirectOperandLowerRegisterLimit) {
	testOperandReturnsType("a0", OperandTypes::AddressRegisterDirect);
}

TEST(OperandFactoryTests, AddressDirectOperandUpperRegisterLimit) {
	testOperandReturnsType("a7", OperandTypes::AddressRegisterDirect);
}

TEST(OperandFactoryTests, AddressDirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("a8", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressDirectOperandExceedsLength) {
	testOperandReturnsType("a21", OperandTypes::InvalidOperand);
}

//===========================================================
// Address Register Indirect
//===========================================================

TEST(OperandFactoryTests, AddressIndirectOperandUpperCase) {
	testOperandReturnsType("(A1)", OperandTypes::AddressRegisterIndirect);
}

TEST(OperandFactoryTests, AddressIndirectOperandLowerCase) {
	testOperandReturnsType("(a1)", OperandTypes::AddressRegisterIndirect);
}

TEST(OperandFactoryTests, AddressIndirectOperandLowerLimit) {
	testOperandReturnsType("(a0)", OperandTypes::AddressRegisterIndirect);
}

TEST(OperandFactoryTests, AddressIndirectOperandUpperLimit) {
	testOperandReturnsType("(a7)", OperandTypes::AddressRegisterIndirect);
}

TEST(OperandFactoryTests, AddressIndirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("(a8)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectOperandInvalidRegister) {
	testOperandReturnsType("(d7)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectOperandExceedsLength) {
	testOperandReturnsType("(a31)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectOperandInvalidLength) {
	testOperandReturnsType("(a1", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectOperandNoParentheses) {
	testOperandReturnsType("!a1$", OperandTypes::InvalidOperand);
}

//===========================================================
// Address Register Indirect with Post Increment
//===========================================================

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandUpperCase) {
	testOperandReturnsType("(A1)+", OperandTypes::AddressRegisterIndirectPostIncrement);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandLowerCase) {
	testOperandReturnsType("(a1)+", OperandTypes::AddressRegisterIndirectPostIncrement);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandLowerLimit) {
	testOperandReturnsType("(a0)+", OperandTypes::AddressRegisterIndirectPostIncrement);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandUpperLimit) {
	testOperandReturnsType("(a7)+", OperandTypes::AddressRegisterIndirectPostIncrement);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("(a8)+", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandInvalidRegister) {
	testOperandReturnsType("(d7)+", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandExceedsLength) {
	testOperandReturnsType("(a31)+", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandInvalidOperator) {
	testOperandReturnsType("(a2)$", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPostIncrementOperandNoParentheses) {
	testOperandReturnsType("!a3@+", OperandTypes::InvalidOperand);
}

//===========================================================
// Address Register Indirect with Pre Decrement
//===========================================================

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandUpperCase) {
	testOperandReturnsType("-(A1)", OperandTypes::AddressRegisterIndirectPreDecrement);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandLowerCase) {
	testOperandReturnsType("-(a1)", OperandTypes::AddressRegisterIndirectPreDecrement);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandLowerLimit) {
	testOperandReturnsType("-(a0)", OperandTypes::AddressRegisterIndirectPreDecrement);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandUpperLimit) {
	testOperandReturnsType("-(a7)", OperandTypes::AddressRegisterIndirectPreDecrement);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("-(a8)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandInvalidRegister) {
	testOperandReturnsType("-(d7)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandExceedsLength) {
	testOperandReturnsType("-(a31)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandInvalidOperator) {
	testOperandReturnsType("$(a2)", OperandTypes::InvalidOperand);
}

TEST(OperandFactoryTests, AddressIndirectPreDecrementOperandNoParentheses) {
	testOperandReturnsType("-!a3@", OperandTypes::InvalidOperand);
}

//===========================================================
// Address Register Indirect with Displacement
//===========================================================

//(d16,An) or d16(An)

// TEST(OperandFactoryTests, AddressRegisterIndirectDisplacementDecimalDisplacement) {
// 	testOperandReturnsType("(134,a1)", )
// }
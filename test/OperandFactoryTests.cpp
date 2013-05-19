#include "gtest/gtest.h"
#include "OperandFactory.h"

void testOperandReturnsType(std::string operand, std::string expectedType) {
	OperandFactory *operandFactory = OperandFactory::getInstance();
	std::string actualType = operandFactory->getOperandType(operand);
	EXPECT_EQ(expectedType, actualType);
}

TEST(OperandFactoryTests, DataDirectOperandUpperCase) {
	testOperandReturnsType("D1", "data direct");
}

TEST(OperandFactoryTests, DataDirectOperandLowerCase) {
	testOperandReturnsType("d1", "data direct");
}

TEST(OperandFactoryTests, DataDirectOperandLowerRegisterLimit) {
	testOperandReturnsType("d0", "data direct");
}

TEST(OperandFactoryTests, DataDirectOperandUpperRegisterLimit) {
	testOperandReturnsType("d7", "data direct");
}

TEST(OperandFactoryTests, DataDirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("d8", "invalid");
}

TEST(OperandFactoryTests, DataDirectOperandExceedsLength) {
	testOperandReturnsType("d00", "invalid");
}

TEST(OperandFactoryTests, AddressDirectOperandUpperCase) {
	testOperandReturnsType("A1", "address direct");
}

TEST(OperandFactoryTests, AddressDirectOperandLowerCase) {
	testOperandReturnsType("a1", "address direct");
}

TEST(OperandFactoryTests, AddressDirectOperandLowerRegisterLimit) {
	testOperandReturnsType("a0", "address direct");
}

TEST(OperandFactoryTests, AddressDirectOperandUpperRegisterLimit) {
	testOperandReturnsType("a7", "address direct");
}

TEST(OperandFactoryTests, AddressDirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("a8", "invalid");
}

TEST(OperandFactoryTests, AddressDirectOperandExceedsLength) {
	testOperandReturnsType("a21", "invalid");
}

TEST(OperandFactoryTests, AddressIndirectOperandUpperCase) {
	testOperandReturnsType("(A1)", "address indirect");
}

TEST(OperandFactoryTests, AddressIndirectOperandLowerCase) {
	testOperandReturnsType("(a1)", "address indirect");
}

TEST(OperandFactoryTests, AddressIndirectOperandLowerLimit) {
	testOperandReturnsType("(a0)", "address indirect");
}

TEST(OperandFactoryTests, AddressIndirectOperandUpperLimit) {
	testOperandReturnsType("(a7)", "address indirect");
}

TEST(OperandFactoryTests, AddressIndirectOperandExceedsUpperRegisterLimit) {
	testOperandReturnsType("(a8)", "invalid");
}

TEST(OperandFactoryTests, AddressIndirectOperandInvalidRegister) {
	testOperandReturnsType("(d7)", "invalid");
}

TEST(OperandFactoryTests, AddressIndirectOperandExceedsLength) {
	testOperandReturnsType("(a31)", "invalid");
}

TEST(OperandFactoryTests, AddressIndirectOperandInvalidLength) {
	testOperandReturnsType("(a1", "invalid");
}
#include "AddressRegisterIndirectPreDecrementOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

bool AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement(const std::string &operand) {
	const unsigned int REQUIRED_LENGTH = 5;
	if(OperandUtils::isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	const unsigned int DECREMENT_OPERATOR_POSITION = 0;
	char preOperator = operand[DECREMENT_OPERATOR_POSITION];
	if(preOperator != '-')
		return false;

	std::string indirectRegister = operand.substr(1, 4);
	return OperandUtils::isIndirectAddressRegister(indirectRegister);
}

AddressRegisterIndirectPreDecrementOperand::AddressRegisterIndirectPreDecrementOperand(const std::string &operand) {
	throwExceptionIfInvalidOperand(operand);
	registerNumber = OperandUtils::getRegisterNumber(operand, REGISTER_NUMBER_POSITION);
}

void AddressRegisterIndirectPreDecrementOperand::throwExceptionIfInvalidOperand(const std::string &operand) {
	if(!isAddressRegisterIndirectPreDecrement(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register indirect with pre decrement operand.");
}

unsigned int AddressRegisterIndirectPreDecrementOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void AddressRegisterIndirectPreDecrementOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for address register indirect with pre decrement operands.");
}

unsigned short *AddressRegisterIndirectPreDecrementOperand::getExtensionWords() const {
	throw LogicException("Cannot get extension words for address register indirect with pre decrement operands.");
}

void AddressRegisterIndirectPreDecrementOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for address register indirect with pre decrement operands.");
}

unsigned int AddressRegisterIndirectPreDecrementOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int AddressRegisterIndirectPreDecrementOperand::getModeField() const {
	return MODE_FIELD;
}

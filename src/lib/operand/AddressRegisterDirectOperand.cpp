#include "AddressRegisterDirectOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

#include <cstdlib>

AddressRegisterDirectOperand::AddressRegisterDirectOperand(const std::string &operand) {
	throwExceptionIfInvalidOperand(operand);
	registerNumber = getRegisterNumber(operand);
}

void AddressRegisterDirectOperand::throwExceptionIfInvalidOperand(const std::string &operand) {
	if(!OperandUtils::isAddressRegister(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register direct operand.");
}

unsigned int AddressRegisterDirectOperand::getRegisterNumber(const std::string &operand) {
	return (unsigned int)(operand[1]) - '0';
}

unsigned int AddressRegisterDirectOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void AddressRegisterDirectOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for address register direct operands.");
}

unsigned short *AddressRegisterDirectOperand::getExtensionWords() const {
	throw LogicException("Cannot get extension words for address register direct operands.");
}

void AddressRegisterDirectOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for address register direct operands.");
}

unsigned int AddressRegisterDirectOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int AddressRegisterDirectOperand::getModeField() const {
	return MODE_FIELD;
}

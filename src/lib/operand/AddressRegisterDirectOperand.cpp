#include "AddressRegisterDirectOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

#include <cstdlib>

bool AddressRegisterDirectOperand::isAddressRegisterDirect(const std::string &operand) {
	return OperandUtils::isAddressRegister(operand);
}

AddressRegisterDirectOperand::AddressRegisterDirectOperand(const std::string &operand) {
	throwExceptionIfInvalidOperand(operand);
	registerNumber = OperandUtils::getRegisterNumber(operand, REGISTER_NUMBER_POSITION);
}

void AddressRegisterDirectOperand::throwExceptionIfInvalidOperand(const std::string &operand) {
	if(!isAddressRegisterDirect(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register direct operand.");
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

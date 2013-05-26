#include "AddressRegisterIndirectOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

#include <cstdlib>

bool AddressRegisterIndirectOperand::isAddressRegisterIndirect(const std::string &operand) {
	if(!OperandUtils::isIndirectRegister(operand))
		return false;

	std::string addressRegister = operand.substr(1, 2);
	if(!OperandUtils::isAddressRegister(addressRegister))
		return false;

	return true;
}

AddressRegisterIndirectOperand::AddressRegisterIndirectOperand(const std::string &operand) {
	throwExceptionIfInvalidOperand(operand);
	registerNumber = OperandUtils::getRegisterNumber(operand, REGISTER_NUMBER_POSITION);
}

void AddressRegisterIndirectOperand::throwExceptionIfInvalidOperand(const std::string &operand) {
	if(!isAddressRegisterIndirect(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register indirect operand.");
}

unsigned int AddressRegisterIndirectOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void AddressRegisterIndirectOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for address register indirect operands.");
}

unsigned short *AddressRegisterIndirectOperand::getExtensionWords() const {
	throw LogicException("Cannot get extension words for address register indirect operands.");
}

void AddressRegisterIndirectOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for address register indirect operands.");
}

unsigned int AddressRegisterIndirectOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int AddressRegisterIndirectOperand::getModeField() const {
	return MODE_FIELD;
}

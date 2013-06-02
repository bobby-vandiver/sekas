#include "AddressRegisterIndirectPostIncrementOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

bool AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement(const std::string &operand) {
	const unsigned int REQUIRED_LENGTH = 5;
	if(OperandUtils::isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	const unsigned int INCREMENT_OPERATOR_POSITION = 4;
	char postOperator = operand[INCREMENT_OPERATOR_POSITION];
	if(postOperator != '+')
		return false;

	std::string indirectRegister = operand.substr(0, 4);
	return OperandUtils::isIndirectAddressRegister(indirectRegister);
}

AddressRegisterIndirectPostIncrementOperand::AddressRegisterIndirectPostIncrementOperand(const std::string &operand) {
	this->operand = operand;
	throwExceptionIfInvalidOperand();
	this->registerNumber = OperandUtils::getRegisterNumber(operand, REGISTER_NUMBER_POSITION);
}

void AddressRegisterIndirectPostIncrementOperand::throwExceptionIfInvalidOperand() const {
	if(!isAddressRegisterIndirectPostIncrement(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register indirect with post increment operand.");
}

unsigned int AddressRegisterIndirectPostIncrementOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void AddressRegisterIndirectPostIncrementOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for address register indirect with post increment operands.");
}

unsigned short *AddressRegisterIndirectPostIncrementOperand::getExtensionWords() const {
	throw LogicException("Cannot get extension words for address register indirect with post increment operands.");
}

void AddressRegisterIndirectPostIncrementOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for address register indirect with post increment operands.");
}

unsigned int AddressRegisterIndirectPostIncrementOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int AddressRegisterIndirectPostIncrementOperand::getModeField() const {
	return MODE_FIELD;
}

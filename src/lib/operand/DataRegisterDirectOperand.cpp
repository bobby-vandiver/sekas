#include "DataRegisterDirectOperand.h"
#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

#include <cstdlib>

DataRegisterDirectOperand::DataRegisterDirectOperand(const std::string &operand) {
	throwExceptionIfInvalidOperand(operand);
	registerNumber = getRegisterNumber(operand);
}

void DataRegisterDirectOperand::throwExceptionIfInvalidOperand(const std::string &operand) {
	if(!OperandUtils::isDataRegister(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid data direct operand.");
}

unsigned int DataRegisterDirectOperand::getRegisterNumber(const std::string &operand) {
	return (unsigned int)(operand[1]) - '0';

}

unsigned int DataRegisterDirectOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void DataRegisterDirectOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for data register direct operands.");
}

unsigned short *DataRegisterDirectOperand::getExtensionWords() const {
	throw LogicException("Cannot get extension words for data register direct operands.");
}

void DataRegisterDirectOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for data register direct operands.");
}

unsigned int DataRegisterDirectOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int DataRegisterDirectOperand::getModeField() const {
	return MODE_FIELD;
}

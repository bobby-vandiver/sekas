#include "AddressRegisterIndirectDisplacementOperand.h"

#include "OperandUtils.h"
#include "LogicException.h"
#include "InvalidOperandException.h"

bool AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement(const std::string &operand) {
	if(isUsingStandardDisplacementNotation(operand))
		return isValidAddressRegisterIndirectWithStandardDisplacementNotation(operand);
	else if(isUsingPrefixDisplacementNotation(operand))
		return isValidAddressRegisterIndirectWithPrefixDisplacementNotation(operand);
	else
		return false;
}

bool AddressRegisterIndirectDisplacementOperand::isUsingStandardDisplacementNotation(const std::string &operand) {
	unsigned int lastCharPosition = operand.length() - 1;
	unsigned int commaPosition = operand.find(',');

	bool isOpenParenthesisFirst = operand[0] == '(';
	bool isClosingParenthesisLast = operand[lastCharPosition] == ')';
	bool containsComma = operand.find(',') != std::string::npos;

	return isOpenParenthesisFirst && isClosingParenthesisLast && containsComma;
}

bool AddressRegisterIndirectDisplacementOperand::isValidAddressRegisterIndirectWithStandardDisplacementNotation(const std::string &operand) {
	std::string displacement = getStandardDisplacement(operand);
	if(!OperandUtils::isValidDisplacement(displacement, MAX_DISPLACEMENT))
		return false;

	unsigned int registerStartPosition = operand.find(',') + 1;
	unsigned int registerEndPosition = operand.length() - 1;
	unsigned int registerLength = registerEndPosition - registerStartPosition;

	std::string specifedRegister = operand.substr(registerStartPosition, registerLength);
	if(!OperandUtils::isAddressRegister(specifedRegister))
		return false;

	return true;
}

const std::string AddressRegisterIndirectDisplacementOperand::getStandardDisplacement(const std::string &operand) {
	unsigned int commaPosition = operand.find(',');
	unsigned int displacementLength = commaPosition - 1;
	return operand.substr(1, displacementLength);
}

bool AddressRegisterIndirectDisplacementOperand::isUsingPrefixDisplacementNotation(const std::string &operand) {
	unsigned int lastCharPosition = operand.length() - 1;
	unsigned int openParenthesisPosition = operand.find('(');
	bool hasOpenParenthesis = openParenthesisPosition != std::string::npos;
	bool hasClosingParenthesis = operand[lastCharPosition] == ')';
	bool doesNotHaveComma = operand.find(',') == std::string::npos;
	return hasOpenParenthesis && hasClosingParenthesis && doesNotHaveComma;
}

bool AddressRegisterIndirectDisplacementOperand::isValidAddressRegisterIndirectWithPrefixDisplacementNotation(const std::string &operand) {
	std::string displacement = getPrefixDisplacement(operand);
	if(!OperandUtils::isValidDisplacement(displacement, MAX_DISPLACEMENT))
		return false;

	unsigned int registerStartPosition = operand.find('(') + 1;
	unsigned int registerEndPosition = operand.length() - 1;
	unsigned int registerLength = registerEndPosition - registerStartPosition;

	std::string specifedRegister = operand.substr(registerStartPosition, registerLength);
	if(!OperandUtils::isAddressRegister(specifedRegister))
		return false;

	return true;
}

const std::string AddressRegisterIndirectDisplacementOperand::getPrefixDisplacement(const std::string &operand) {
	unsigned int openParenthesisPosition = operand.find('(');
	unsigned int displacementLength = openParenthesisPosition;
	return operand.substr(0, displacementLength);
}

AddressRegisterIndirectDisplacementOperand::AddressRegisterIndirectDisplacementOperand(const std::string &operand) {
	this->operand = operand;
	throwExceptionIfInvalidOperand();
	unsigned int registerNumberPosition = getRegisterNumberPosition();
	this->registerNumber = OperandUtils::getRegisterNumber(operand, registerNumberPosition);
	this->extensionWords = getExtensionWordsForDisplacement();
}

unsigned short *AddressRegisterIndirectDisplacementOperand::getExtensionWordsForDisplacement() const {
	std::string displacement;

	if(isUsingStandardDisplacementNotation(operand)) {
		unsigned int commaPosition = operand.find(',');
		unsigned int displacementLength = commaPosition - 1;
		displacement = operand.substr(1, displacementLength);
	}
	else if(isUsingPrefixDisplacementNotation(operand)) {
		unsigned int openParenthesisPosition = operand.find('(');
		unsigned int displacementLength = openParenthesisPosition;
		displacement = operand.substr(0, displacementLength);
	}

	return OperandUtils::getExtensionWordsFromDisplacement(displacement, OperandUtils::WORD_SIZE);
}

void AddressRegisterIndirectDisplacementOperand::throwExceptionIfInvalidOperand() const {
	if(!isAddressRegisterIndirectDisplacement(operand))
		throw InvalidOperandException("Operand [" + operand + "] is not a valid address register indirect with displacement operand.");
}

unsigned int AddressRegisterIndirectDisplacementOperand::getRegisterNumberPosition() const {
	const unsigned int REGISTER_NUMBER_POSITION_FROM_END = 2;
	return operand.length() - REGISTER_NUMBER_POSITION_FROM_END;
}

unsigned int AddressRegisterIndirectDisplacementOperand::getExtensionWordCount() const {
	return EXTENSION_WORD_COUNT;
}

void AddressRegisterIndirectDisplacementOperand::setExtensionWordCount(const unsigned int count) {
	throw LogicException("Cannot set extension word count for address register indirect with displacement operands.");
}

unsigned short *AddressRegisterIndirectDisplacementOperand::getExtensionWords() const {
	return extensionWords;
}

void AddressRegisterIndirectDisplacementOperand::setExtensionWords(unsigned short *extensionWords) {
	throw LogicException("Cannot set extension words for address register indirect with displacement operands.");
}

unsigned int AddressRegisterIndirectDisplacementOperand::getRegisterField() const {
	return registerNumber;
}

unsigned int AddressRegisterIndirectDisplacementOperand::getModeField() const {
	return MODE_FIELD;
}

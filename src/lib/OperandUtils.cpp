#include "OperandUtils.h"

bool OperandUtils::isDataRegister(const std::string &operand) {
	return isValidRegister(operand, 'd', 'D');
}

bool OperandUtils::isAddressRegister(const std::string &operand) {
	return isValidRegister(operand, 'a', 'A');
}

bool OperandUtils::isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType) {
	const unsigned int REQUIRED_LENGTH = 2;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;
	else if(isRegisterTypeInvalid(operand, lowerCaseType, upperCaseType))
		return false;
	else if(isRegisterNumberOutOfRange(operand, '0', '7'))
		return false;
	else
		return true;
}

bool OperandUtils::isIndirectRegister(const std::string &operand) {
	const unsigned int REQUIRED_LENGTH = 4;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;
	else if(operand[0] != '(' || operand[3] != ')')
		return false;
	else
		return true;
}

bool OperandUtils::isOperandInvalidLength(const std::string &operand, const unsigned int length) {
	return exceedsMaxOperandLength(operand, length) || belowMinimumOperandLength(operand, length);
}

bool OperandUtils::exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) {
	return operand.length() > maxLength;
}

bool OperandUtils::belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) {
	return operand.length() < minimumLength;
}

bool OperandUtils::isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) {
	char registerType = operand[0];
	if(registerType != upperCaseType && registerType != lowerCaseType)
		return true;
	else
		return false;
}

bool OperandUtils::isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) {
	char registerNumber = operand[1];
	if(registerNumber < lowerBound || registerNumber > upperBound)
		return true;
	else
		return false;
}


bool OperandUtils::isValidDisplacement(const std::string &displacement) {
	return isValidDecimalDisplacement(displacement) || isValidHexadecimalDisplacement(displacement);
}

bool OperandUtils::isValidDecimalDisplacement(const std::string &displacement) {
	for(unsigned int i = 0; i < displacement.length(); i++) {
		if(displacement[i] < '0' || displacement[i] > '9')
			return false;
	}
	return true;
}

bool OperandUtils::isValidHexadecimalDisplacement(const std::string &displacement) {
	if(displacement[0] != '$')
		return false;

	for(unsigned int i = 1; i < displacement.length(); i++) {
		char c = displacement[i];

		bool isNumeric = (c >= '0') && (c <= '9');
		bool isUpperAlpha = (c >= 'A') && (c <= 'F');
		bool isLowerAlpha = (c >= 'a') && (c <= 'f');

		if(!isNumeric && !isUpperAlpha && !isLowerAlpha)
			return false;
	}
	return true;
}

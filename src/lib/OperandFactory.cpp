#include "OperandFactory.h"

OperandFactory *OperandFactory::instance = NULL;

OperandFactory::~OperandFactory() {
	delete instance;
}

OperandFactory *OperandFactory::getInstance() {
	if(!instance)
		instance = new OperandFactory();
	return instance;
}

std::string OperandFactory::getOperandType(const std::string &operand) const {
	if(isDataRegisterDirect(operand))
		return "data direct";
	else if(isAddressRegisterDirect(operand))
		return "address direct";
	else if(isAddressRegisterIndirect(operand))
		return "address indirect";
	else if(isAddressRegisterIndirectPostIncrement(operand))
		return "address indirect post increment";
	else if(isAddressRegisterIndirectPreDecrement(operand))
		return "address indirect pre decrement";
	else
		return "invalid";
}

bool OperandFactory::isDataRegisterDirect(const std::string &operand) const {
	return isDataRegister(operand);
}

bool OperandFactory::isDataRegister(const std::string &operand) const {
	return isValidRegister(operand, 'd', 'D');
}

bool OperandFactory::isAddressRegister(const std::string &operand) const {
	return isValidRegister(operand, 'a', 'A');
}

bool OperandFactory::isAddressRegisterDirect(const std::string &operand) const {
	return isAddressRegister(operand);
}

bool OperandFactory::isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType) const {
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

bool OperandFactory::isAddressRegisterIndirect(const std::string &operand) const {
	if(!isIndirectRegister(operand))
		return false;

	std::string specifedRegister = operand.substr(1, 2);
	if(!isAddressRegister(specifedRegister))
		return false;

	return true;
}

bool OperandFactory::isIndirectRegister(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 4;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;
	else if(operand[0] != '(' || operand[3] != ')')
		return false;
	else
		return true;
}

bool OperandFactory::isAddressRegisterIndirectPostIncrement(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 5;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	char postOperator = operand[4];
	if(postOperator != '+')
		return false;

	std::string indirectRegister = operand.substr(0, 4);
	return isAddressRegisterIndirect(indirectRegister);
}

bool OperandFactory::isAddressRegisterIndirectPreDecrement(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 5;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	char preOperator = operand[0];
	if(preOperator != '-')
		return false;

	std::string indirectRegister = operand.substr(1, 4);
	return isAddressRegisterIndirect(indirectRegister);
}

bool OperandFactory::isOperandInvalidLength(const std::string &operand, const unsigned int length) const {
	return exceedsMaxOperandLength(operand, length) || belowMinimumOperandLength(operand, length);
}

bool OperandFactory::exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) const {
	return operand.length() > maxLength;
}

bool OperandFactory::belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) const {
	return operand.length() < minimumLength;
}

bool OperandFactory::isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) const {
	char registerType = operand[0];
	if(registerType != upperCaseType && registerType != lowerCaseType)
		return true;
	else
		return false;
}

bool OperandFactory::isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) const {
	char registerNumber = operand[1];
	if(registerNumber < lowerBound || registerNumber > upperBound)
		return true;
	else
		return false;
}


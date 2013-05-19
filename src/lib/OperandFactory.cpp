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
	else
		return "invalid";
}

bool OperandFactory::isDataRegisterDirect(const std::string &operand) const {
	if(isOperandInvalidLength(operand, 2))
		return false;
	else if(isRegisterTypeInvalid(operand, 'd', 'D'))
		return false;
	else if(isRegisterNumberOutOfRange(operand, '0', '7'))
		return false;
	else
		return true;
}

bool OperandFactory::isAddressRegisterDirect(const std::string &operand) const {
	if(isOperandInvalidLength(operand, 2))
		return false;
	else if(isRegisterTypeInvalid(operand, 'a', 'A'))
		return false;
	else if(isRegisterNumberOutOfRange(operand, '0', '7'))
		return false;
	else
		return true;
}

bool OperandFactory::isAddressRegisterIndirect(const std::string &operand) const {
	if(isOperandInvalidLength(operand, 4))
		return false;

	std::string specifedRegister = operand.substr(1, 2);
	if(!isAddressRegisterDirect(specifedRegister))
		return false;

	return true;
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


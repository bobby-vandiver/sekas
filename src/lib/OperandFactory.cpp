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

std::string OperandFactory::getOperandType(std::string operand) const {
	if(isDataRegisterDirect(operand))
		return "data direct";
	else if(isAddressRegisterDirect(operand))
		return "address direct";
	else
		return "invalid";
}

bool OperandFactory::isDataRegisterDirect(std::string operand) const {
	if(exceedsMaxDirectRegisterOperandLength(operand))
		return false;
	else if(isRegisterTypeInvalid(operand, 'd', 'D'))
		return false;
	else if(isRegisterNumberOutOfRange(operand, '0', '7'))
		return false;
	else
		return true;
}

bool OperandFactory::isAddressRegisterDirect(std::string operand) const {
	if(exceedsMaxDirectRegisterOperandLength(operand))
		return false;
	else if(isRegisterTypeInvalid(operand, 'a', 'A'))
		return false;
	else if(isRegisterNumberOutOfRange(operand, '0', '7'))
		return false;
	else
		return true;
}

bool OperandFactory::exceedsMaxDirectRegisterOperandLength(std::string operand) const {
	const unsigned int MAX_LENGTH = 2;
	return operand.length() > MAX_LENGTH;
}

bool OperandFactory::isRegisterTypeInvalid(std::string operand, char lowerCaseType, char upperCaseType) const {
	char registerType = operand[0];
	if(registerType != upperCaseType && registerType != lowerCaseType)
		return true;
	else
		return false;
}

bool OperandFactory::isRegisterNumberOutOfRange(std::string operand, char lowerBound, char upperBound) const {
	char registerNumber = operand[1];
	if(registerNumber < lowerBound || registerNumber > upperBound)
		return true;
	else
		return false;
}


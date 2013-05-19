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

	char registerType = operand[0];
	if(registerType != 'D' && registerType != 'd')
		return false;

	char registerNumber = operand[1];
	if(registerNumber < '0' || registerNumber > '7')
		return false;

	return true;
}

bool OperandFactory::exceedsMaxDirectRegisterOperandLength(std::string operand) const {
	const unsigned int MAX_LENGTH = 2;
	return operand.length() > MAX_LENGTH;
}
bool OperandFactory::isAddressRegisterDirect(std::string operand) const {
	if(exceedsMaxDirectRegisterOperandLength(operand))
		return false;

	char registerType = operand[0];
	if(registerType != 'A' && registerType != 'a')
		return false;

	return true;
}


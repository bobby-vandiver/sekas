#include "OperandFactory.h"
#include "OperandTypes.h"
#include "OperandUtils.h"

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
		return OperandTypes::DataRegisterDirect;
	else if(isAddressRegisterDirect(operand))
		return OperandTypes::AddressRegisterDirect;
	else if(isAddressRegisterIndirect(operand))
		return OperandTypes::AddressRegisterIndirect;
	else if(isAddressRegisterIndirectPostIncrement(operand))
		return OperandTypes::AddressRegisterIndirectPostIncrement;
	else if(isAddressRegisterIndirectPreDecrement(operand))
		return OperandTypes::AddressRegisterIndirectPreDecrement;
	else if(isAddressRegisterIndirectDisplacement(operand))
		return OperandTypes::AddressRegisterIndirectDisplacement;
	else
		return OperandTypes::InvalidOperand;
}

bool OperandFactory::isDataRegisterDirect(const std::string &operand) const {
	return OperandUtils::isDataRegister(operand);
}

bool OperandFactory::isAddressRegisterDirect(const std::string &operand) const {
	return OperandUtils::isAddressRegister(operand);
}

bool OperandFactory::isAddressRegisterIndirect(const std::string &operand) const {
	if(!OperandUtils::isIndirectRegister(operand))
		return false;

	std::string specifedRegister = operand.substr(1, 2);
	if(!OperandUtils::isAddressRegister(specifedRegister))
		return false;

	return true;
}

bool OperandFactory::isAddressRegisterIndirectPostIncrement(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 5;
	if(OperandUtils::isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	char postOperator = operand[4];
	if(postOperator != '+')
		return false;

	std::string indirectRegister = operand.substr(0, 4);
	return isAddressRegisterIndirect(indirectRegister);
}

bool OperandFactory::isAddressRegisterIndirectPreDecrement(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 5;
	if(OperandUtils::isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;

	char preOperator = operand[0];
	if(preOperator != '-')
		return false;

	std::string indirectRegister = operand.substr(1, 4);
	return isAddressRegisterIndirect(indirectRegister);
}

bool OperandFactory::isAddressRegisterIndirectDisplacement(const std::string &operand) const {
	if(isUsingStandardDisplacementNotation(operand))
		return isValidAddressRegisterIndirectWithStandardDisplacementNotation(operand);

	return false;
}

bool OperandFactory::isUsingStandardDisplacementNotation(const std::string &operand) const {
	unsigned int lastCharPosition = operand.length() - 1;
	return (operand[0] == '(') && (operand[lastCharPosition] == ')');
}

bool OperandFactory::isValidAddressRegisterIndirectWithStandardDisplacementNotation(const std::string &operand) const {
	unsigned int commaPosition = operand.find(',');
	if(commaPosition == std::string::npos)
		return false;

	unsigned int displacementLength = commaPosition - 1;
	std::string displacement = operand.substr(1, displacementLength);
	if(!OperandUtils::isValidDisplacement(displacement))
		return false;

	unsigned int registerStartPosition = commaPosition + 1;
	unsigned int registerEndPosition = operand.length() - 1;
	unsigned int registerLength = registerEndPosition - registerStartPosition;

	std::string specifedRegister = operand.substr(registerStartPosition, registerLength);
	if(!OperandUtils::isAddressRegister(specifedRegister))
		return false;

	return true;
}

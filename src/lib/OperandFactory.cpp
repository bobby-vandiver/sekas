#include "OperandFactory.h"
#include "OperandTypes.h"

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
	return isDataRegister(operand);
}

bool OperandFactory::isAddressRegisterDirect(const std::string &operand) const {
	return isAddressRegister(operand);
}

bool OperandFactory::isAddressRegisterIndirect(const std::string &operand) const {
	if(!isIndirectRegister(operand))
		return false;

	std::string specifedRegister = operand.substr(1, 2);
	if(!isAddressRegister(specifedRegister))
		return false;

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
	if(!isValidDisplacement(displacement))
		return false;

	unsigned int registerStartPosition = commaPosition + 1;
	unsigned int registerEndPosition = operand.length() - 1;
	unsigned int registerLength = registerEndPosition - registerStartPosition;

	std::string specifedRegister = operand.substr(registerStartPosition, registerLength);
	if(!isAddressRegister(specifedRegister))
		return false;

	return true;
}

bool OperandFactory::isValidDisplacement(const std::string &displacement) const {
	return isValidDecimalDisplacement(displacement) || isValidHexadecimalDisplacement(displacement);
}

bool OperandFactory::isValidDecimalDisplacement(const std::string &displacement) const {
	for(unsigned int i = 0; i < displacement.length(); i++) {
		if(displacement[i] < '0' || displacement[i] > '9')
			return false;
	}
	return true;
}

bool OperandFactory::isValidHexadecimalDisplacement(const std::string &displacement) const {
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

bool OperandFactory::isDataRegister(const std::string &operand) const {
	return isValidRegister(operand, 'd', 'D');
}

bool OperandFactory::isAddressRegister(const std::string &operand) const {
	return isValidRegister(operand, 'a', 'A');
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

bool OperandFactory::isIndirectRegister(const std::string &operand) const {
	const unsigned int REQUIRED_LENGTH = 4;
	if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
		return false;
	else if(operand[0] != '(' || operand[3] != ')')
		return false;
	else
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


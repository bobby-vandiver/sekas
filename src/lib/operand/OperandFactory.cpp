#include "OperandFactory.h"
#include "OperandTypes.h"
#include "OperandUtils.h"

#include "DataRegisterDirectOperand.h"
#include "AddressRegisterDirectOperand.h"
#include "AddressRegisterIndirectOperand.h"
#include "AddressRegisterIndirectPostIncrementOperand.h"
#include "AddressRegisterIndirectPreDecrementOperand.h"

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
	return DataRegisterDirectOperand::isDataRegisterDirect(operand);
}

bool OperandFactory::isAddressRegisterDirect(const std::string &operand) const {
	return AddressRegisterDirectOperand::isAddressRegisterDirect(operand);
}

bool OperandFactory::isAddressRegisterIndirect(const std::string &operand) const {
	return AddressRegisterIndirectOperand::isAddressRegisterIndirect(operand);
}

bool OperandFactory::isAddressRegisterIndirectPostIncrement(const std::string &operand) const {
	return AddressRegisterIndirectPostIncrementOperand::isAddressRegisterIndirectPostIncrement(operand);
}

bool OperandFactory::isAddressRegisterIndirectPreDecrement(const std::string &operand) const {
	return AddressRegisterIndirectPreDecrementOperand::isAddressRegisterIndirectPreDecrement(operand);
}

bool OperandFactory::isAddressRegisterIndirectDisplacement(const std::string &operand) const {
	if(isUsingStandardDisplacementNotation(operand))
		return isValidAddressRegisterIndirectWithStandardDisplacementNotation(operand);
	else if(isUsingPrefixDisplacementNotation(operand))
		return isValidAddressRegisterIndirectWithPrefixDisplacementNotation(operand);
	else
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

bool OperandFactory::isUsingPrefixDisplacementNotation(const std::string &operand) const {
	unsigned int lastCharPosition = operand.length() - 1;
	unsigned int openParenthesisPosition = operand.find('(');
	bool hasOpenParenthesis = openParenthesisPosition != std::string::npos;
	bool hasClosingParenthesis = operand[lastCharPosition] == ')';
	return hasOpenParenthesis && hasClosingParenthesis;
}

bool OperandFactory::isValidAddressRegisterIndirectWithPrefixDisplacementNotation(const std::string &operand) const {
	unsigned int openParenthesisPosition = operand.find('(');

	unsigned int displacementLength = openParenthesisPosition;
	std::string displacement = operand.substr(0, displacementLength);
	if(!OperandUtils::isValidDisplacement(displacement))
		return false;

	unsigned int registerStartPosition = openParenthesisPosition + 1;
	unsigned int registerEndPosition = operand.length() - 1;
	unsigned int registerLength = registerEndPosition - registerStartPosition;

	std::string specifedRegister = operand.substr(registerStartPosition, registerLength);
	if(!OperandUtils::isAddressRegister(specifedRegister))
		return false;

	return true;
}
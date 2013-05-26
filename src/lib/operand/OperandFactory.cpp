#include "OperandFactory.h"
#include "OperandTypes.h"
#include "OperandUtils.h"

#include "DataRegisterDirectOperand.h"
#include "AddressRegisterDirectOperand.h"
#include "AddressRegisterIndirectOperand.h"
#include "AddressRegisterIndirectPostIncrementOperand.h"
#include "AddressRegisterIndirectPreDecrementOperand.h"
#include "AddressRegisterIndirectDisplacementOperand.h"

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
	return AddressRegisterIndirectDisplacementOperand::isAddressRegisterIndirectDisplacement(operand);
}

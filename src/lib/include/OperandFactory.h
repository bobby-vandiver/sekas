#ifndef OPERAND_FACTORY_H
#define OPERAND_FACTORY_H

#include <string>

class OperandFactory {
public:
	static OperandFactory* getInstance();
	std::string getOperandType(const std::string &operand) const;

private:
	OperandFactory() {}
	~OperandFactory();
	static OperandFactory *instance;

	bool isDataRegisterDirect(const std::string &operand) const;
	bool isAddressRegisterDirect(const std::string &operand) const;
	bool isAddressRegisterIndirect(const std::string &operand) const;
	bool isAddressRegisterIndirectPostIncrement(const std::string &operand) const;
	bool isAddressRegisterIndirectPreDecrement(const std::string &operand) const;
	bool isAddressRegisterIndirectDisplacement(const std::string &operand) const;

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length) const;
	bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) const;
	bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) const;

	bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) const;
	bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) const;

	bool isDataRegister(const std::string &operand) const;
	bool isAddressRegister(const std::string &operand) const;

	bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType) const;
	bool isIndirectRegister(const std::string &operand) const;

	bool isUsingStandardDisplacementNotation(const std::string &operand) const;
	bool isValidAddressRegisterIndirectWithStandardDisplacementNotation(const std::string &operand) const;
	
	bool isValidDisplacement(const std::string &displacement) const;
	bool isValidDecimalDisplacement(const std::string &displacement) const;
	bool isValidHexadecimalDisplacement(const std::string &displacement) const;

};

#endif
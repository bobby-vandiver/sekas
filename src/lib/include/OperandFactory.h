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

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length) const;
	bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) const;
	bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) const;

	bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) const;
	bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) const;
};

#endif
#ifndef OPERAND_FACTORY_H
#define OPERAND_FACTORY_H

#include <string>

class OperandFactory {
public:
	static OperandFactory* getInstance();
	std::string getOperandType(std::string operand) const;

private:
	OperandFactory() {}
	~OperandFactory();
	static OperandFactory *instance;

	bool isDataRegisterDirect(std::string operand) const;
	bool isAddressRegisterDirect(std::string operand) const;

	bool exceedsMaxDirectRegisterOperandLength(std::string operand) const;
	bool isRegisterTypeInvalid(std::string operand, char lowerCaseType, char upperCaseType) const;
	bool isRegisterNumberOutOfRange(std::string operand, char lowerBound, char upperBound) const;
};

#endif
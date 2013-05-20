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

	bool isUsingStandardDisplacementNotation(const std::string &operand) const;
	bool isValidAddressRegisterIndirectWithStandardDisplacementNotation(const std::string &operand) const;
};

#endif
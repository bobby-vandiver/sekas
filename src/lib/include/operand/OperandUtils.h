#ifndef OPERAND_UTILS_H
#define OPERAND_UTILS_H

#include <string>

namespace OperandUtils {
	bool isDataRegister(const std::string &operand);
	bool isAddressRegister(const std::string &operand);
	bool isIndirectRegister(const std::string &operand);

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length);

	unsigned int getRegisterNumber(const std::string &operand, const unsigned int position);

	bool isValidDisplacement(const std::string &displacement);
}

#endif
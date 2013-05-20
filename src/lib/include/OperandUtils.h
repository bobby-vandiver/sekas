#ifndef OPERAND_UTILS_H
#define OPERAND_UTILS_H

#include <string>

namespace OperandUtils {
	bool isOperandInvalidLength(const std::string &operand, const unsigned int length);
	bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength);
	bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength);

	bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType);
	bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound);

	bool isDataRegister(const std::string &operand);
	bool isAddressRegister(const std::string &operand);

	bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType);
	bool isIndirectRegister(const std::string &operand);

	bool isValidDisplacement(const std::string &displacement);
	bool isValidDecimalDisplacement(const std::string &displacement);
	bool isValidHexadecimalDisplacement(const std::string &displacement);
}

#endif
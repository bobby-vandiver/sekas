#ifndef OPERAND_UTILS_H
#define OPERAND_UTILS_H

#include <string>

namespace OperandUtils {
	bool isDataRegister(const std::string &operand);
	bool isAddressRegister(const std::string &operand);
	bool isIndirectAddressRegister(const std::string &operand);

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length);

	unsigned int getRegisterNumber(const std::string &operand, const unsigned int position);

	bool isValidDisplacement(const std::string &displacement);
	bool isValidDisplacement(const std::string &displacement, unsigned long maxDisplacement);

	const unsigned long MAX_WORD_VALUE = 0xffff;
	const unsigned long MAX_LONG_VALUE = 0xffffffff;

	const unsigned int WORD_SIZE = 1;
	const unsigned int LONG_SIZE = 2;

	unsigned short *getExtensionWordsFromDisplacement(const std::string &displacement, const unsigned int size);
}

#endif
#include "OperandUtils.h"
#include "NumberUtils.h"
#include "IllegalArgumentException.h"

#include <cctype>
#include <sstream>

namespace OperandUtils {
	static bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType);

	bool isDataRegister(const std::string &operand) {
		return isValidRegister(operand, 'd', 'D');
	}

	bool isAddressRegister(const std::string &operand) {
		return isValidRegister(operand, 'a', 'A');
	}

	static void throwExceptionIfLowerCaseAndUpperCaseRepresentDifferentCharacter(char lowerCaseType, char upperCaseType);
	static bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType);
	static bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound);

	static bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType) {
		const unsigned int REQUIRED_LENGTH = 2;

		throwExceptionIfLowerCaseAndUpperCaseRepresentDifferentCharacter(lowerCaseType, upperCaseType);

		if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
			return false;
		else if(isRegisterTypeInvalid(operand, lowerCaseType, upperCaseType))
			return false;
		else if(isRegisterNumberOutOfRange(operand, '0', '7'))
			return false;
		else
			return true;
	}

	static void throwExceptionIfLowerCaseAndUpperCaseRepresentDifferentCharacter(char lowerCaseType, char upperCaseType) {
		if(toupper(lowerCaseType) != upperCaseType) {
			std::ostringstream messageStream;
			messageStream << "lower case register type [" << lowerCaseType << "]";
			messageStream << "must represent same register as upper case [" << upperCaseType << "]";
			throw IllegalArgumentException(messageStream.str());
		}
	}

	static bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength);
	static bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength);

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length) {
		return exceedsMaxOperandLength(operand, length) || belowMinimumOperandLength(operand, length);
	}

	static bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) {
		return operand.length() > maxLength;
	}

	static bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) {
		return operand.length() < minimumLength;
	}

	static bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) {
		char registerType = operand[0];
		if(registerType != upperCaseType && registerType != lowerCaseType)
			return true;
		else
			return false;
	}

	static bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) {
		char registerNumber = operand[1];
		if(registerNumber < lowerBound || registerNumber > upperBound)
			return true;
		else
			return false;
	}

	static bool isIndirectRegister(const std::string &operand);

	bool isIndirectAddressRegister(const std::string &operand) {
		if(!isIndirectRegister(operand))
			return false;

		std::string addressRegister = operand.substr(1, 2);
		if(!isAddressRegister(addressRegister))
			return false;

		return true;
	}

	static bool isIndirectRegister(const std::string &operand) {
		const unsigned int REQUIRED_LENGTH = 4;
		if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
			return false;
		else if(operand[0] != '(' || operand[3] != ')')
			return false;
		else
			return true;
	}

	static void throwIfPositionIsInvalid(const std::string &operand, const unsigned int position);
	static void throwIfRegisterNumberIsInvalid(char registerNumber);
	static unsigned int convertRegisterNumberToUnsignedInt(char registerNumber);

	unsigned int getRegisterNumber(const std::string &operand, const unsigned int position) {
		throwIfPositionIsInvalid(operand, position);	
		char registerNumber = operand[position];
		throwIfRegisterNumberIsInvalid(registerNumber);
		return convertRegisterNumberToUnsignedInt(registerNumber);
	}

	static void throwIfPositionIsInvalid(const std::string &operand, const unsigned int position) {
		unsigned int length = operand.length();
		if(position > length) {
			std::ostringstream messageStream;
			messageStream << "Position [" << position << "] is invalid for [" << operand << "].";
			throw IllegalArgumentException(messageStream.str());
		}
	}

	static void throwIfRegisterNumberIsInvalid(char registerNumber) {
		if(registerNumber < '0' || registerNumber > '9') {
			std::ostringstream messageStream;
			messageStream << "Register number [" << registerNumber << "] is invalid.";
			throw IllegalArgumentException(messageStream.str());
		}
	}

	static unsigned int convertRegisterNumberToUnsignedInt(char registerNumber) {
		return (unsigned int)(registerNumber) - '0';
	}

	bool isValidDisplacement(const std::string &displacement) {
		return NumberUtils::isValidNumber(displacement);
	}

	bool isValidDisplacement(const std::string &displacement, unsigned long maxDisplacement) {
		if(!isValidDisplacement(displacement))
			return false;

		unsigned long displacementValue = NumberUtils::parseNumber(displacement);
		return displacementValue <= maxDisplacement;
	}

	static void throwIfWordDisplacementExpectedButActualExceedsMaxWordValue(const unsigned long displacement, const unsigned int size) {
		if(size == WORD_SIZE && displacement > MAX_WORD_VALUE) {
			std::ostringstream messageStream;
			messageStream << "Size specified [" << size << "]";
			messageStream << "is incompatible with displacement [" << displacement << "].";
			throw IllegalArgumentException(messageStream.str());
		}
	}

	static void throwExceptionForInvalidDisplacementSize(const unsigned long displacement, const unsigned int size) {
		std::ostringstream messageStream;
		messageStream << "Size specified [" << size << "]";
		messageStream << "for displacement [" << displacement << "] is invalid.";
		throw IllegalArgumentException(messageStream.str());
	}

	unsigned short *getExtensionWordsFromDisplacement(const std::string &displacement, const unsigned int size) {
		unsigned long displacementValue = NumberUtils::parseNumber(displacement);
		unsigned short *extensionWords = new unsigned short[size];

		throwIfWordDisplacementExpectedButActualExceedsMaxWordValue(displacementValue, size);

		if(size == WORD_SIZE) {
			extensionWords[0] = displacementValue & 0xffff;
		}
		else if(size == LONG_SIZE) {
			extensionWords[0] = (displacementValue & 0xffff0000) >> 16;
			extensionWords[1] = displacementValue & 0xffff;
		}
		else {
			throwExceptionForInvalidDisplacementSize(displacementValue, size);
		}
		return extensionWords;
	}
}
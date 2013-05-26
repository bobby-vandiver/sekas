#include "OperandUtils.h"
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

	static bool isValidDisplacementLength(const std::string &displacement);
	static bool isValidDecimalDisplacement(const std::string &displacement);
	static bool isValidHexadecimalDisplacement(const std::string &displacement);

	bool isValidDisplacement(const std::string &displacement) {
		return isValidDecimalDisplacement(displacement) || isValidHexadecimalDisplacement(displacement);
	}

	static bool isValidDecimalDisplacement(const std::string &displacement) {
		const unsigned int MINIMUM_LENGTH = 1;

		unsigned int length = displacement.length();
		if(length < MINIMUM_LENGTH)
			return false;

		for(unsigned int i = 0; i < displacement.length(); i++) {
			if(displacement[i] < '0' || displacement[i] > '9')
				return false;
		}
		return true;
	}

	static bool isValidHexadecimalDisplacement(const std::string &displacement) {
		const unsigned int MINIMUM_LENGTH = 1;

		unsigned int length = displacement.length();
		if(length <= MINIMUM_LENGTH)
			return false;

		if(displacement[0] != '$')
			return false;

		for(unsigned int i = 1; i < displacement.length(); i++) {
			char c = displacement[i];

			bool isNumeric = (c >= '0') && (c <= '9');
			bool isUpperAlpha = (c >= 'A') && (c <= 'F');
			bool isLowerAlpha = (c >= 'a') && (c <= 'f');

			if(!isNumeric && !isUpperAlpha && !isLowerAlpha)
				return false;
		}
		return true;
	}
}
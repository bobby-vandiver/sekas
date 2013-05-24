#include "OperandUtils.h"
#include "IllegalArgumentException.h"

#include <cctype>
#include <sstream>

namespace OperandUtils {
	bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType);

	void throwExceptionIfLowerCaseAndUpperCaseRepresentDifferentCharacter(char lowerCaseType, char upperCaseType);
	bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType);
	bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound);

	bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength);
	bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength);


	bool isValidDisplacementLength(const std::string &displacement);
	bool isValidDecimalDisplacement(const std::string &displacement);
	bool isValidHexadecimalDisplacement(const std::string &displacement);


	bool isDataRegister(const std::string &operand) {
		return isValidRegister(operand, 'd', 'D');
	}

	bool isAddressRegister(const std::string &operand) {
		return isValidRegister(operand, 'a', 'A');
	}

	bool isValidRegister(const std::string &operand, char lowerCaseType, char upperCaseType) {
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

	void throwExceptionIfLowerCaseAndUpperCaseRepresentDifferentCharacter(char lowerCaseType, char upperCaseType) {
		if(toupper(lowerCaseType) != upperCaseType) {
			std::ostringstream messageStream;
			messageStream << "lower case register type [" << lowerCaseType << "]";
			messageStream << "must represent same register as upper case [" << upperCaseType << "]";
			throw IllegalArgumentException(messageStream.str());
		}
	}

	bool isIndirectRegister(const std::string &operand) {
		const unsigned int REQUIRED_LENGTH = 4;
		if(isOperandInvalidLength(operand, REQUIRED_LENGTH))
			return false;
		else if(operand[0] != '(' || operand[3] != ')')
			return false;
		else
			return true;
	}

	bool isOperandInvalidLength(const std::string &operand, const unsigned int length) {
		return exceedsMaxOperandLength(operand, length) || belowMinimumOperandLength(operand, length);
	}

	bool exceedsMaxOperandLength(const std::string &operand, const unsigned int maxLength) {
		return operand.length() > maxLength;
	}

	bool belowMinimumOperandLength(const std::string &operand, const unsigned int minimumLength) {
		return operand.length() < minimumLength;
	}

	bool isRegisterTypeInvalid(const std::string &operand, char lowerCaseType, char upperCaseType) {
		char registerType = operand[0];
		if(registerType != upperCaseType && registerType != lowerCaseType)
			return true;
		else
			return false;
	}

	bool isRegisterNumberOutOfRange(const std::string &operand, char lowerBound, char upperBound) {
		char registerNumber = operand[1];
		if(registerNumber < lowerBound || registerNumber > upperBound)
			return true;
		else
			return false;
	}


	bool isValidDisplacement(const std::string &displacement) {
		return isValidDecimalDisplacement(displacement) || isValidHexadecimalDisplacement(displacement);
	}

	bool isValidDecimalDisplacement(const std::string &displacement) {
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

	bool isValidHexadecimalDisplacement(const std::string &displacement) {
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
#include "NumberUtils.h"
#include "IllegalArgumentException.h"

#include <sstream>

namespace NumberUtils {
	static bool isValidDecimalNumber(const std::string &number);
	static bool isValidHexadecimalNumber(const std::string &number);

	bool isValidNumber(const std::string &number) {
		return isValidDecimalNumber(number) || isValidHexadecimalNumber(number);
	}

	static bool isValidDecimalNumber(const std::string &number) {
		const unsigned int MINIMUM_LENGTH = 1;

		unsigned int length = number.length();
		if(length < MINIMUM_LENGTH)
			return false;

		for(unsigned int i = 0; i < number.length(); i++) {
			if(number[i] < '0' || number[i] > '9')
				return false;
		}
		return true;
	}

	static bool isValidHexadecimalNumber(const std::string &number) {
		const unsigned int MINIMUM_LENGTH = 1;

		unsigned int length = number.length();
		if(length <= MINIMUM_LENGTH)
			return false;

		if(number[0] != '$')
			return false;

		for(unsigned int i = 1; i < number.length(); i++) {
			char c = number[i];

			bool isNumeric = (c >= '0') && (c <= '9');
			bool isUpperAlpha = (c >= 'A') && (c <= 'F');
			bool isLowerAlpha = (c >= 'a') && (c <= 'f');

			if(!isNumeric && !isUpperAlpha && !isLowerAlpha)
				return false;
		}
		return true;
	}

	static unsigned int charToValue(const char c, const char minimumChar, const unsigned int offset);
	static void throwInvalidNumberCannotBeParsed(const std::string &number);

	static unsigned long parseDecimalNumber(const std::string &number);
	static unsigned int charToDecimalValue(const char c);

	static unsigned long parseHexadecimalNumber(const std::string &number);
	static unsigned int charToHexadecimalValue(const char c);

	static unsigned long power(const unsigned int base, const unsigned int power);

	unsigned long parseNumber(const std::string &number) {
		if(isValidDecimalNumber(number))
			return parseDecimalNumber(number);
		else if(isValidHexadecimalNumber(number))
			return parseHexadecimalNumber(number);
		else
			throwInvalidNumberCannotBeParsed(number);
	}

	static unsigned long parseDecimalNumber(const std::string &number) {
		const unsigned int BASE = 10;

		unsigned int exponent = 0;
		int position = number.length() - 1;

		unsigned long result = 0;
		while(position >= 0) {
			char digit = number[position--];
			unsigned int digitValue = charToDecimalValue(digit);
			result += digitValue * power(BASE, exponent++);
		}
		return result;
	}

	static unsigned int charToDecimalValue(const char c) {
		const unsigned int OFFSET = 0;
		return charToValue(c, '0', OFFSET);
	}

	static unsigned long parseHexadecimalNumber(const std::string &number) {
		const unsigned int BASE = 16;
		const unsigned int DOLLAR_SIGN_POSITION = 0;

		unsigned int exponent = 0;
		int position = number.length() - 1;

		unsigned long result = 0;
		while(position > DOLLAR_SIGN_POSITION) {
			char digit = number[position--];
			unsigned int digitValue = charToHexadecimalValue(digit);
			result += digitValue * power(BASE, exponent++);
		}
		return result;
	}

	static void throwInvalidHexadecimalDigit(const char c);

	static unsigned int charToHexadecimalValue(const char c) {
		const unsigned int NUMERIC_OFFSET = 0;
		const unsigned int ALPHA_OFFSET = 0xa;

		bool isNumeric = (c >= '0') && (c <= '9');
		bool isUpperAlpha = (c >= 'A') && (c <= 'F');
		bool isLowerAlpha = (c >= 'a') && (c <= 'f');

		if(isNumeric)
			return charToValue(c, '0', NUMERIC_OFFSET);
		else if(isUpperAlpha)
			return charToValue(c, 'A', ALPHA_OFFSET);
		else if(isLowerAlpha)
			return charToValue(c, 'a', ALPHA_OFFSET);
		else
			throwInvalidHexadecimalDigit(c);
	}

	static void throwInvalidHexadecimalDigit(const char c) {
		std::ostringstream messageStream;
		messageStream << "Invalid hexadecimal char [" << c << "].";
		throw IllegalArgumentException(messageStream.str());
	}

	static unsigned int charToValue(const char c, const char minimumChar, const unsigned int offset) {
		return ((unsigned int)c - minimumChar) + offset;
	}
	
	static unsigned long power(const unsigned int base, const unsigned int exponent) {
		unsigned long result = 1;
		for(unsigned int i = 0; i < exponent; i++) {
			result *= base;
		}
		return result;
	}

	static void throwInvalidNumberCannotBeParsed(const std::string &number) {
		std::ostringstream messageStream;
		messageStream << "Invalid number [" << number << "] cannot be parsed.";
		throw IllegalArgumentException(messageStream.str());
	}
}
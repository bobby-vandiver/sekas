#include "Symbol.h"
#include "IllegalArgumentException.h"

bool Symbol::isValid(const std::string symbol) {
	const unsigned int INVALID_CHARS_COUNT = 3;
	const char INVALID_CHARS[INVALID_CHARS_COUNT] = { '$', '#', '%' };

	bool startsWithInvalidChar = false;
	for(unsigned int i = 0; i < INVALID_CHARS_COUNT; i++) {
		if(symbol[0] == INVALID_CHARS[i])
			startsWithInvalidChar = true;
	}

	bool isEmpty = (symbol.length() == 0);
	bool startsWithDigit = (symbol[0] >= '0' && symbol[0] <= '9');
	return !isEmpty && !startsWithDigit && !startsWithInvalidChar;
}

Symbol::Symbol(std::string name, unsigned long address)
	: name(name), address(address) {

	if(!isValid(name))
		throw IllegalArgumentException("Symbol: [" + name + "] is invalid.");
}

std::string Symbol::getName() const {
	return name;
}

unsigned long Symbol::getAddress() const {
	return address;
}

void Symbol::setAddress(unsigned long address) {
	this->address = address;
}
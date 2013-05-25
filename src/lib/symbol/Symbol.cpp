#include "Symbol.h"

std::string Symbol::getName() const {
	return name;
}

unsigned long Symbol::getAddress() const {
	return address;
}

void Symbol::setAddress(unsigned long address) {
	this->address = address;
}
#include "Symbol.h"

Symbol::Symbol(std::string name, unsigned long address) {
	this->name = name;
	this->address = address;
}

std::string Symbol::getName() {
	return name;
}

unsigned long Symbol::getAddress() {
	return address;
}

void Symbol::setAddress(unsigned long address) {
	this->address = address;
}
#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

class Symbol {

	static const unsigned long DEFAULT_ADDRESS = 0;

public:
	Symbol(std::string name, unsigned long address = DEFAULT_ADDRESS)
		: name(name), address(address) {}

	std::string getName() const;

	unsigned long getAddress() const;
	void setAddress(unsigned long address);

private:
	std::string name;
	unsigned long address;
};

#endif
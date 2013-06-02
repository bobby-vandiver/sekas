#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

class Symbol {
public:
	static bool isValid(const std::string symbol);

	Symbol(std::string name, unsigned long address = DEFAULT_ADDRESS);

	std::string getName() const;

	unsigned long getAddress() const;
	void setAddress(unsigned long address);

private:
	static const unsigned long DEFAULT_ADDRESS = 0;

	std::string name;
	unsigned long address;
};

#endif
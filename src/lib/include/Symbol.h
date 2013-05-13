#include <string>

class Symbol {

	static const unsigned long DEFAULT_ADDRESS = 0;

public:
	Symbol(std::string name, unsigned long address = DEFAULT_ADDRESS);

	std::string getName();

	unsigned long getAddress();
	void setAddress(unsigned long address);

private:
	std::string name;
	unsigned long address;
};
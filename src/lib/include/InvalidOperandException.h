#ifndef INVALID_OPERAND_EXCEPTION_H
#define INVALID_OPERAND_EXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidOperandException : public std::runtime_error {
public:
	explicit InvalidOperandException(const std::string message) :
		runtime_error(message) {}
};

#endif
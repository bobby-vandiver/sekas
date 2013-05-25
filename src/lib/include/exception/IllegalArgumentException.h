#ifndef ILLEGAL_ARGUMENT_EXCEPTION_H
#define ILLEGAL_ARGUMENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class IllegalArgumentException : public std::invalid_argument {
public:
	explicit IllegalArgumentException(const std::string message) :
		invalid_argument(message) {}
};

#endif
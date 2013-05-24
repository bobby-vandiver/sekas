#ifndef LOGIC_EXCEPTION_H
#define LOGIC_EXCEPTION_H

#include <stdexcept>
#include <string>

class LogicException : public std::logic_error {
public:
	explicit LogicException(const std::string message) :
		logic_error(message) {}
};

#endif
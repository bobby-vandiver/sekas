#ifndef NUMBER_UTILS_H
#define NUMBER_UTILS_H

#include <string>

namespace NumberUtils {
	const unsigned long MAX_NUMBER_ALLOWED = 0xffffffff;
	unsigned long parseNumber(const std::string &number);

	bool isValidNumber(const std::string &number);
}

#endif
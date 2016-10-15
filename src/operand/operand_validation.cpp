#include "operand_validation.h"

#include <string>
#include <stdexcept>

namespace {
    const uint8_t MAX_DATA_REGISTER_NUMBER = 7;
    const uint8_t MAX_ADDRESS_REGISTER_NUMBER = 7;

    uint8_t validate_register_number(const uint8_t register_number,
                                     const uint8_t max_register_number,
                                     const std::string message) {
        if (register_number > max_register_number) {
            throw std::invalid_argument(message);
        }
        return register_number;
    }
}

uint8_t operand_validation::validate_data_register_number(const uint8_t register_number) {
    return validate_register_number(register_number, MAX_DATA_REGISTER_NUMBER,
                                    "data register number must be between 0 and 7");
}

uint8_t operand_validation::validate_address_register_number(const uint8_t register_number) {
    return validate_register_number(register_number, MAX_ADDRESS_REGISTER_NUMBER,
                                    "address register must be between 0 and 7");
}
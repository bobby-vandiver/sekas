#ifndef SEKAS_OPERAND_VALIDATION_H
#define SEKAS_OPERAND_VALIDATION_H

#include <cstdint>

namespace OperandValidation {
    uint8_t validate_data_register_number(const uint8_t register_number);
    uint8_t validate_address_register_number(const uint8_t register_number);
}

#endif

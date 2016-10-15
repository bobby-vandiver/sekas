#include "address_direct_operand.h"

namespace {
    const uint8_t MAX_ADDRESS_REGISTER_NUMBER = 7;

    uint8_t validate_address_register_number(const uint8_t register_number) {
        if (register_number > MAX_ADDRESS_REGISTER_NUMBER) {
            throw std::invalid_argument("address register must be between 0 and 7");
        }
        return register_number;
    }
}

address_direct_operand::address_direct_operand(const uint8_t register_number) :
        register_number(validate_address_register_number(register_number)) {
}

address_direct_operand::~address_direct_operand() {
}

uint8_t address_direct_operand::get_mode_field() const {
    return 1; // 001
}

uint8_t address_direct_operand::get_register_field() const {
    return register_number;
}

uint8_t address_direct_operand::get_extension_word_count() const {
    return 0;
}

uint16_t address_direct_operand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("address direct operands do not have extension words");
}
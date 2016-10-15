#include "data_direct_operand.h"

namespace {
    const uint8_t MAX_DATA_REGISTER_NUMBER = 7;
}

data_direct_operand::data_direct_operand(const uint8_t register_number) {
    if (register_number > MAX_DATA_REGISTER_NUMBER) {
        throw std::invalid_argument("data register number must be between 0 and 7");
    }
    this->register_number = register_number;
}

data_direct_operand::~data_direct_operand() {
}

uint8_t data_direct_operand::get_mode_field() const {
    return 0; // 000
}

uint8_t data_direct_operand::get_register_field() const {
    return register_number;
}

uint8_t data_direct_operand::get_extension_word_count() const {
    return 0;
}

uint16_t data_direct_operand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("data direct operands do not have extension words");
}
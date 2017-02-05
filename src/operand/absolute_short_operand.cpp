#include "absolute_short_operand.h"

AbsoluteShortOperand::AbsoluteShortOperand(const uint16_t address) :
        address(address) {
}

AbsoluteShortOperand::~AbsoluteShortOperand() {
}

uint8_t AbsoluteShortOperand::get_mode_field() const {
    return 0b111;
}

uint8_t AbsoluteShortOperand::get_register_field() const {
    return 0b000;
}

uint8_t AbsoluteShortOperand::get_extension_word_count() const {
    return 1;
}

uint16_t AbsoluteShortOperand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("absolute short operands have only one extension word");
    }
    return address;
}
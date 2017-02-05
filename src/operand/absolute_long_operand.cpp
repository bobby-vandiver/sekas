#include "absolute_long_operand.h"

AbsoluteLongOperand::AbsoluteLongOperand(const uint32_t address) :
        address(address) {
}

AbsoluteLongOperand::~AbsoluteLongOperand() {
}

uint8_t AbsoluteLongOperand::get_mode_field() const {
    return 0b111;
}

uint8_t AbsoluteLongOperand::get_register_field() const {
    return 0b001;
}

uint8_t AbsoluteLongOperand::get_extension_word_count() const {
    return 2;
}

uint16_t AbsoluteLongOperand::get_extension_word(const uint8_t idx) const {
    if (idx > 1) {
        throw std::invalid_argument("absolute long operands have only two extension words");
    }

    if (idx == 0) {
        return static_cast<uint16_t>((address & 0xffff0000) >> 16);
    }
    return static_cast<uint16_t>(address & 0xffff);
}
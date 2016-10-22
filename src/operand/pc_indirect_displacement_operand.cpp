#include "pc_indirect_displacement_operand.h"

ProgramCounterIndirectDisplacementOperand::ProgramCounterIndirectDisplacementOperand(const int16_t displacement) :
        displacement(displacement) {
}

ProgramCounterIndirectDisplacementOperand::~ProgramCounterIndirectDisplacementOperand() {
}

uint8_t ProgramCounterIndirectDisplacementOperand::get_mode_field() const {
    return 0b111;
}

uint8_t ProgramCounterIndirectDisplacementOperand::get_register_field() const {
    return 0b010;
}

uint8_t ProgramCounterIndirectDisplacementOperand::get_extension_word_count() const {
    return 1;
}

uint16_t ProgramCounterIndirectDisplacementOperand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("pc indirect with displacement operands have only one extension word");
    }
    return static_cast<uint16_t>(displacement);
}
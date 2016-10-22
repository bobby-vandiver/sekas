#include "pc_indirect_index_operand.h"

ProgramCounterIndirectIndexOperand::ProgramCounterIndirectIndexOperand(const int8_t displacement,
                                                                       IndexRegister *index_register) :
        displacement(displacement),
        index_register(std::unique_ptr<IndexRegister>(index_register)) {
}

ProgramCounterIndirectIndexOperand::~ProgramCounterIndirectIndexOperand() {
}

uint8_t ProgramCounterIndirectIndexOperand::get_mode_field() const {
    return 0b111;
}

uint8_t ProgramCounterIndirectIndexOperand::get_register_field() const {
    return 0b011;
}

uint8_t ProgramCounterIndirectIndexOperand::get_extension_word_count() const {
    return 1;
}

uint16_t ProgramCounterIndirectIndexOperand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("pc indirect with index operands have only one extension word");
    }

    uint8_t encoded_index_register = index_register->encode();
    uint16_t extension_word = static_cast<uint16_t>(encoded_index_register) << 8;

    extension_word &= 0xff00;
    extension_word |= static_cast<uint8_t>(displacement);

    return extension_word;
}
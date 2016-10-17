#include "address_indirect_index_operand.h"
#include "operand_validation.h"

address_indirect_index_operand::address_indirect_index_operand(const uint8_t register_number,
                                                               const uint8_t displacement,
                                                               index_register::ptr index_register) :
        register_number(operand_validation::validate_address_register_number(register_number)),
        displacement(displacement),
        index(std::move(index_register)) {
}

address_indirect_index_operand::~address_indirect_index_operand() {
}

uint8_t address_indirect_index_operand::get_mode_field() const {
    return 0b110;
}

uint8_t address_indirect_index_operand::get_register_field() const {
    return register_number;
}

uint8_t address_indirect_index_operand::get_extension_word_count() const {
    return 1;
}

uint16_t address_indirect_index_operand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("address indirect with index operands have only one extension word");
    }

    // TODO: Encode index register
    uint16_t extension_word = static_cast<uint16_t>(displacement);
    extension_word &= 0xff;
    return extension_word;
}
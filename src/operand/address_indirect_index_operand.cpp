#include "address_indirect_index_operand.h"
#include "operand_validation.h"

AddressIndirectIndexOperand::AddressIndirectIndexOperand(const uint8_t register_number,
                                                         const int8_t displacement,
                                                         IndexRegister *index_register) :
        register_number(operand_validation::validate_address_register_number(register_number)),
        displacement(displacement),
        index_register(std::unique_ptr<IndexRegister>(index_register)) {
}

AddressIndirectIndexOperand::~AddressIndirectIndexOperand() {
}

uint8_t AddressIndirectIndexOperand::get_mode_field() const {
    return 0b110;
}

uint8_t AddressIndirectIndexOperand::get_register_field() const {
    return register_number;
}

uint8_t AddressIndirectIndexOperand::get_extension_word_count() const {
    return 1;
}

uint16_t AddressIndirectIndexOperand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("address indirect with index operands have only one extension word");
    }

    uint8_t encoded_index_register = index_register->encode();
    uint16_t extension_word = static_cast<uint16_t>(encoded_index_register) << 8;

    extension_word &= 0xff00;
    extension_word |= static_cast<uint8_t>(displacement);

    return extension_word;
}
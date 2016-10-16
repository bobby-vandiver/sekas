#include "address_indirect_postincrement_operand.h"
#include "operand_validation.h"

address_indirect_postincrement_operand::address_indirect_postincrement_operand(const uint8_t register_number) :
        register_number(operand_validation::validate_address_register_number(register_number)) {
}

address_indirect_postincrement_operand::~address_indirect_postincrement_operand() {
}

uint8_t address_indirect_postincrement_operand::get_mode_field() const {
    return 0b011;
}

uint8_t address_indirect_postincrement_operand::get_register_field() const {
    return register_number;
}

uint8_t address_indirect_postincrement_operand::get_extension_word_count() const {
    return 0;
}

uint16_t address_indirect_postincrement_operand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("address indirect with postincrement operands do not have extension words");
}
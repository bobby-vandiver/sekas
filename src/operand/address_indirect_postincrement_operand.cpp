#include "address_indirect_postincrement_operand.h"
#include "operand_validation.h"

AddressIndirectPostincrementOperand::AddressIndirectPostincrementOperand(const uint8_t register_number) :
        register_number(OperandValidation::validate_address_register_number(register_number)) {
}

AddressIndirectPostincrementOperand::~AddressIndirectPostincrementOperand() {
}

uint8_t AddressIndirectPostincrementOperand::get_mode_field() const {
    return 0b011;
}

uint8_t AddressIndirectPostincrementOperand::get_register_field() const {
    return register_number;
}

uint8_t AddressIndirectPostincrementOperand::get_extension_word_count() const {
    return 0;
}

uint16_t AddressIndirectPostincrementOperand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("address indirect with postincrement operands do not have extension words");
}
#include "address_indirect_predecrement_operand.h"
#include "operand_validation.h"

AddressIndirectPredecrementOperand::AddressIndirectPredecrementOperand(const uint8_t register_number) :
        register_number(OperandValidation::validate_address_register_number(register_number)) {
}

AddressIndirectPredecrementOperand::~AddressIndirectPredecrementOperand() {
}

uint8_t AddressIndirectPredecrementOperand::get_mode_field() const {
    return 0b100;
}

uint8_t AddressIndirectPredecrementOperand::get_register_field() const {
    return register_number;
}

uint8_t AddressIndirectPredecrementOperand::get_extension_word_count() const {
    return 0;
}

uint16_t AddressIndirectPredecrementOperand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("address indirect with predecrement operands do not have extension words");
}
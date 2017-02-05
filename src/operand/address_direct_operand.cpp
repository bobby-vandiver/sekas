#include "address_direct_operand.h"
#include "operand_validation.h"

AddressDirectOperand::AddressDirectOperand(const uint8_t register_number) :
        register_number(OperandValidation::validate_address_register_number(register_number)) {
}

AddressDirectOperand::~AddressDirectOperand() {
}

uint8_t AddressDirectOperand::get_mode_field() const {
    return 0b001;
}

uint8_t AddressDirectOperand::get_register_field() const {
    return register_number;
}

uint8_t AddressDirectOperand::get_extension_word_count() const {
    return 0;
}

uint16_t AddressDirectOperand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("address direct operands do not have extension words");
}
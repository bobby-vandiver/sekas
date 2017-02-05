#include "address_indirect_displacement_operand.h"
#include "operand_validation.h"

AddressIndirectDisplacementOperand::AddressIndirectDisplacementOperand(const uint8_t register_number,
                                                                       const int16_t displacement) :
        register_number(OperandValidation::validate_address_register_number(register_number)),
        displacement(displacement) {
}

AddressIndirectDisplacementOperand::~AddressIndirectDisplacementOperand() {
}

uint8_t AddressIndirectDisplacementOperand::get_mode_field() const {
    return 0b101;
}

uint8_t AddressIndirectDisplacementOperand::get_register_field() const {
    return register_number;
}

uint8_t AddressIndirectDisplacementOperand::get_extension_word_count() const {
    return 1;
}

uint16_t AddressIndirectDisplacementOperand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("address indirect with displacement operands have only one extension word");
    }
    return static_cast<uint16_t>(displacement);
}
#include "address_indirect_displacement_operand.h"
#include "operand_validation.h"

address_indirect_displacement_operand::address_indirect_displacement_operand(const uint8_t register_number,
                                                                             const uint16_t displacement) :
        register_number(operand_validation::validate_address_register_number(register_number)),
        displacement(displacement) {
}

address_indirect_displacement_operand::~address_indirect_displacement_operand() {
}

uint8_t address_indirect_displacement_operand::get_mode_field() const {
    return 0b101;
}

uint8_t address_indirect_displacement_operand::get_register_field() const {
    return register_number;
}

uint8_t address_indirect_displacement_operand::get_extension_word_count() const {
    return 1;
}

uint16_t address_indirect_displacement_operand::get_extension_word(const uint8_t idx) const {
    if (idx != 0) {
        throw std::invalid_argument("address indirect with displacement operands have only one extension word");
    }
    return displacement;
}
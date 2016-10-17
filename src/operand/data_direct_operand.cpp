#include "data_direct_operand.h"
#include "operand_validation.h"

DataDirectOperand::DataDirectOperand(const uint8_t register_number) :
        register_number(operand_validation::validate_data_register_number(register_number)) {
}

DataDirectOperand::~DataDirectOperand() {
}

uint8_t DataDirectOperand::get_mode_field() const {
    return 0b000;
}

uint8_t DataDirectOperand::get_register_field() const {
    return register_number;
}

uint8_t DataDirectOperand::get_extension_word_count() const {
    return 0;
}

uint16_t DataDirectOperand::get_extension_word(const uint8_t idx) const {
    throw std::invalid_argument("data direct operands do not have extension words");
}
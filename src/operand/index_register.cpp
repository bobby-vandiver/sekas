#include "index_register.h"
#include "operand_validation.h"

namespace {
    uint8_t validate_register_number(const uint8_t register_number, const index_register::type type) {
        if (type == index_register::type::DATA) {
            return operand_validation::validate_data_register_number(register_number);
        }
        else {
            return operand_validation::validate_address_register_number(register_number);
        }
    }
}

index_register::index_register(const uint8_t register_number,
                               index_register::type type,
                               index_register::size size,
                               index_register::scale scale):
        register_number(validate_register_number(register_number, type)),
        index_type(type),
        index_size(size),
        index_scale(scale) {
}

index_register::~index_register() {
}

uint8_t index_register::get_register_number() const {
    return register_number;
}

index_register::type index_register::get_type() const {
    return index_type;
}

index_register::size index_register::get_size() const {
    return index_size;
}

index_register::scale index_register::get_scale() const {
    return index_scale;
}

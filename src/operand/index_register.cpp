#include "index_register.h"
#include "operand_validation.h"
#include <map>

namespace {
    uint8_t validate_register_number(const uint8_t register_number, const index_register::type type) {
        if (type == index_register::type::DATA) {
            return operand_validation::validate_data_register_number(register_number);
        }
        else {
            return operand_validation::validate_address_register_number(register_number);
        }
    }

    const std::map<index_register::type, uint8_t> register_type_field_mapping {
            {index_register::type::DATA, 0b0},
            {index_register::type::ADDRESS, 0b1},
    };

    const std::map<index_register::size, uint8_t> size_field_mapping {
            {index_register::size::WORD, 0b0},
            {index_register::size::LONG_WORD, 0b1}
    };

    const std::map<index_register::scale, uint8_t> scale_field_mapping {
            {index_register::scale::ONE, 0b00},
            {index_register::scale::TWO, 0b01},
            {index_register::scale::FOUR, 0b10},
            {index_register::scale::EIGHT, 0b11},
    };
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

uint8_t index_register::encode() const {
    uint8_t register_field = register_number;
    uint8_t da_field = register_type_field_mapping.at(index_type);
    uint8_t wl_field = size_field_mapping.at(index_size);
    uint8_t scale_field = scale_field_mapping.at(index_scale);

    uint8_t extension_word = 0;

    extension_word |= scale_field << 1;
    extension_word |= wl_field << 3;
    extension_word |= register_field << 4;
    extension_word |= da_field << 7;

    return extension_word;
}
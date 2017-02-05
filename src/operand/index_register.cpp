#include "index_register.h"
#include "operand_validation.h"
#include <map>

namespace {
    uint8_t validate_register_number(const uint8_t register_number, const IndexRegister::Type type) {
        if (type == IndexRegister::Type::DATA) {
            return OperandValidation::validate_data_register_number(register_number);
        }
        else {
            return OperandValidation::validate_address_register_number(register_number);
        }
    }

    const std::map<IndexRegister::Type, uint8_t> register_type_field_mapping {
            {IndexRegister::Type::DATA, 0b0},
            {IndexRegister::Type::ADDRESS, 0b1},
    };

    const std::map<IndexRegister::Size, uint8_t> size_field_mapping {
            {IndexRegister::Size::WORD, 0b0},
            {IndexRegister::Size::LONG_WORD, 0b1}
    };

    const std::map<IndexRegister::Scale, uint8_t> scale_field_mapping {
            {IndexRegister::Scale::ONE, 0b00},
            {IndexRegister::Scale::TWO, 0b01},
            {IndexRegister::Scale::FOUR, 0b10},
            {IndexRegister::Scale::EIGHT, 0b11},
    };
}

IndexRegister::IndexRegister(const uint8_t register_number,
                               IndexRegister::Type type,
                               IndexRegister::Size size,
                               IndexRegister::Scale scale):
        register_number(validate_register_number(register_number, type)),
        type(type),
        size(size),
        scale(scale) {
}

IndexRegister::IndexRegister() :
        IndexRegister(0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE) {
}

IndexRegister::~IndexRegister() {
}

uint8_t IndexRegister::get_register_number() const {
    return register_number;
}

IndexRegister::Type IndexRegister::get_type() const {
    return type;
}

IndexRegister::Size IndexRegister::get_size() const {
    return size;
}

IndexRegister::Scale IndexRegister::get_scale() const {
    return scale;
}

uint8_t IndexRegister::encode() const {
    uint8_t register_field = register_number;
    uint8_t da_field = register_type_field_mapping.at(type);
    uint8_t wl_field = size_field_mapping.at(size);
    uint8_t scale_field = scale_field_mapping.at(scale);

    uint8_t extension_word = 0;

    extension_word |= scale_field << 1;
    extension_word |= wl_field << 3;
    extension_word |= register_field << 4;
    extension_word |= da_field << 7;

    return extension_word;
}
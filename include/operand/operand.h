#ifndef SEKAS_OPERAND_H
#define SEKAS_OPERAND_H

#include <cstdint>

class operand {
public:
    virtual ~operand() {}

    virtual uint8_t get_register_field() = 0;
    virtual uint8_t get_mode_field() = 0;

    virtual uint8_t get_extension_word_count() = 0;
    virtual uint16_t get_extension_word(const uint8_t idx) = 0;
};

#endif

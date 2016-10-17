#ifndef SEKAS_OPERAND_H
#define SEKAS_OPERAND_H

#include <cstdint>
#include <memory>

class Operand {
public:
    typedef std::unique_ptr<Operand> Ptr;

    virtual ~Operand() {}

    virtual uint8_t get_mode_field() const = 0;
    virtual uint8_t get_register_field() const = 0;

    virtual uint8_t get_extension_word_count() const = 0;
    virtual uint16_t get_extension_word(const uint8_t idx) const = 0;
};

#endif

#ifndef SEKAS_IMMEDIATE_OPERAND_H
#define SEKAS_IMMEDIATE_OPERAND_H

#include "operand.h"

class ImmediateOperand : public Operand {
public:
    enum class DataLength {
        BYTE,
        WORD,
        LONG_WORD
    };

    explicit ImmediateOperand(const uint32_t data, DataLength length);
    ~ImmediateOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const ;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const DataLength length;
    const uint32_t data;
};

#endif

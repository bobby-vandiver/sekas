#ifndef SEKAS_ABSOLUTE_SHORT_OPERAND_H
#define SEKAS_ABSOLUTE_SHORT_OPERAND_H

#include "operand.h"

class AbsoluteShortOperand : public Operand {
public:
    explicit AbsoluteShortOperand(const uint16_t address);
    virtual ~AbsoluteShortOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const uint16_t address;
};

#endif

#ifndef SEKAS_ABSOLUTE_LONG_OPERAND_H
#define SEKAS_ABSOLUTE_LONG_OPERAND_H

#include "operand.h"

class AbsoluteLongOperand : public Operand {
public:
    explicit AbsoluteLongOperand(const uint32_t address);
    virtual ~AbsoluteLongOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const ;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const uint32_t address;
};

#endif

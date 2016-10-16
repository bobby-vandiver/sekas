#ifndef SEKAS_ADDRESS_INDIRECT_PREDECREMENT_OPERAND_H
#define SEKAS_ADDRESS_INDIRECT_PREDECREMENT_OPERAND_H

#include "operand.h"

class address_indirect_predecrement_operand : public operand {
public:
    explicit address_indirect_predecrement_operand(const uint8_t register_number);
    virtual ~address_indirect_predecrement_operand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const uint8_t register_number;
};

#endif

#ifndef SEKAS_DATA_DIRECT_OPERAND_H
#define SEKAS_DATA_DIRECT_OPERAND_H

#include "operand.h"

class DataDirectOperand : public Operand {
public:
    explicit DataDirectOperand(const uint8_t register_number);
    virtual ~DataDirectOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const uint8_t register_number;
};

#endif

#ifndef SEKAS_PC_INDIRECT_DISPLACEMENT_OPERAND_H
#define SEKAS_PC_INDIRECT_DISPLACEMENT_OPERAND_H

#include "operand.h"

class ProgramCounterIndirectDisplacementOperand : public Operand {
public:
    explicit ProgramCounterIndirectDisplacementOperand(const int16_t displacement);
    virtual ~ProgramCounterIndirectDisplacementOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const int16_t displacement;
};

#endif

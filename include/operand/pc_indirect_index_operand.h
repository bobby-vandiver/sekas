#ifndef SEKAS_PC_INDIRECT_INDEX_OPERAND_H
#define SEKAS_PC_INDIRECT_INDEX_OPERAND_H

#include "operand.h"
#include "index_register.h"

class ProgramCounterIndirectIndexOperand : public Operand {
public:
    explicit ProgramCounterIndirectIndexOperand(const int8_t displacement, IndexRegister *index_register);
    virtual ~ProgramCounterIndirectIndexOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const int8_t displacement;
    const std::unique_ptr<IndexRegister> index_register;
};

#endif

#ifndef SEKAS_ADDRESS_INDIRECT_INDEX_OPERAND_H
#define SEKAS_ADDRESS_INDIRECT_INDEX_OPERAND_H

#include "operand.h"
#include "index_register.h"

class AddressIndirectIndexOperand : public Operand {
public:
    explicit AddressIndirectIndexOperand(const uint8_t register_number,
                                            const uint8_t displacement,
                                            std::unique_ptr<IndexRegister> index_register);
    virtual ~AddressIndirectIndexOperand();

    virtual uint8_t get_mode_field() const;
    virtual uint8_t get_register_field() const;

    virtual uint8_t get_extension_word_count() const;
    virtual uint16_t get_extension_word(const uint8_t idx) const;

private:
    const uint8_t register_number;
    const uint8_t displacement;
    const std::unique_ptr<IndexRegister> index_register;
};

#endif

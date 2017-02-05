#include <backward/strstream>
#include "immediate_operand.h"
#include "utility/word_extraction.h"

namespace {
    void validate_index(const uint8_t idx, const uint8_t max) {
        if (idx > max) {
            std::strstream message;
            message << "extension word " << idx << "for immediate data is not allowed";
            throw std::invalid_argument(message.str());
        }
    }
}

ImmediateOperand::ImmediateOperand(const uint32_t data, DataLength length) :
        data(data),
        length(length) {
}

ImmediateOperand::~ImmediateOperand() {
}

uint8_t ImmediateOperand::get_mode_field() const {
    return 0b111;
}

uint8_t ImmediateOperand::get_register_field() const {
    return 0b100;
}

uint8_t ImmediateOperand::get_extension_word_count() const {
    if (length == DataLength::BYTE || length == DataLength::WORD) {
        return 1;
    }
    return 2;
}

uint16_t ImmediateOperand::get_extension_word(const uint8_t idx) const {
    if (length == DataLength::BYTE || length == DataLength::WORD) {
        validate_index(idx, 0);
        return WordExtraction::get_low_word(data);
    }

    validate_index(idx, 1);

    if (idx == 0) {
        return WordExtraction::get_high_word(data);
    }
    return WordExtraction::get_low_word(data);
}
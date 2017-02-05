#include <backward/strstream>
#include "immediate_operand.h"

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
        return static_cast<uint16_t>(data & 0xffff);
    }

    validate_index(idx, 1);

    // TODO: Refactor to common place -- copied in AbsoluteLongOperand implementation
    if (idx == 0) {
        return static_cast<uint16_t>((data & 0xffff0000) >> 16);
    }
    return static_cast<uint16_t>(data & 0xffff);
}
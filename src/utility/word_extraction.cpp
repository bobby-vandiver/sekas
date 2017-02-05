#include "utility/word_extraction.h"

uint16_t WordExtraction::get_high_word(const uint32_t data) {
    return static_cast<uint16_t>((data & 0xffff0000) >> 16);
}

uint16_t WordExtraction::get_low_word(const uint32_t data) {
    return static_cast<uint16_t>(data & 0xffff);
}
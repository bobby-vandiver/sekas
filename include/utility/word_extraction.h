#ifndef SEKAS_WORD_EXTRACTION_H
#define SEKAS_WORD_EXTRACTION_H

#include <cstdint>

namespace WordExtraction {
    uint16_t get_high_word(const uint32_t data);
    uint16_t get_low_word(const uint32_t data);
}

#endif

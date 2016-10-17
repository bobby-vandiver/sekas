#include "gtest/gtest.h"
#include "operand/index_register.h"

namespace {
    struct encoding_test_params {

        encoding_test_params(uint8_t register_number,
                             index_register::type type,
                             index_register::size size,
                             index_register::scale scale,
                             uint8_t encoding) :
                register_number(register_number),
                type(type),
                size(size),
                scale(scale),
                encoding(encoding) {
        }

        uint8_t register_number;
        index_register::type type;
        index_register::size size;
        index_register::scale scale;
        uint8_t encoding;
    };


    const encoding_test_params params[] = {
            // Register number
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00000000},
            {1, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00010000},
            {2, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00100000},
            {3, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00110000},
            {4, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b01000000},
            {5, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b01010000},
            {6, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b01100000},
            {7, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b01110000},

            // Register type
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00000000},
            {0, index_register::type::ADDRESS, index_register::size::WORD, index_register::scale::ONE, 0b10000000},

            // Size
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00000000},
            {0, index_register::type::DATA, index_register::size::LONG_WORD, index_register::scale::ONE, 0b00001000},

            // Scale
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::ONE, 0b00000000},
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::TWO, 0b00000010},
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::FOUR, 0b00000100},
            {0, index_register::type::DATA, index_register::size::WORD, index_register::scale::EIGHT, 0b00000110},
    };
}

class IndexRegisterNumberTest : public ::testing::TestWithParam<index_register::type> {
};

class IndexRegisterEncodingTest : public ::testing::TestWithParam<encoding_test_params> {
};

TEST_P(IndexRegisterNumberTest, ValidRegisterNumber) {
    std::array<const uint8_t, 8> numbers = {0, 1, 2, 3, 4, 5, 6, 7};

    for (auto number : numbers) {
        const index_register::type type = GetParam();
        index_register reg(number, type, index_register::size::WORD, index_register::scale::ONE);
        EXPECT_EQ(number, reg.get_register_number());
    }
}

TEST_P(IndexRegisterEncodingTest, CorrectEncoding) {
    encoding_test_params params = GetParam();

    index_register idx_reg(params.register_number, params.type, params.size, params.scale);
    EXPECT_EQ(params.encoding, idx_reg.encode());
}

TEST(IndexRegisterTest, GetProperties) {
    index_register idx_register(1,
                                index_register::type::DATA,
                                index_register::size::LONG_WORD,
                                index_register::scale::FOUR);

    EXPECT_EQ(1, idx_register.get_register_number());
    EXPECT_EQ(index_register::type::DATA, idx_register.get_type());
    EXPECT_EQ(index_register::size::LONG_WORD, idx_register.get_size());
    EXPECT_EQ(index_register::scale::FOUR, idx_register.get_scale());
}

INSTANTIATE_TEST_CASE_P(IndexRegisterNumber, IndexRegisterNumberTest,
                        ::testing::Values(index_register::type::DATA, index_register::type::ADDRESS));

INSTANTIATE_TEST_CASE_P(IndexRegisterEncoding,
                        IndexRegisterEncodingTest,
                        ::testing::ValuesIn(params));

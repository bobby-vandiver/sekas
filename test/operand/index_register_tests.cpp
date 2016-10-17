#include "gtest/gtest.h"
#include "operand/index_register.h"

namespace {
    struct encoding_test_params {

        encoding_test_params(uint8_t register_number,
                             IndexRegister::Type type,
                             IndexRegister::Size size,
                             IndexRegister::Scale scale,
                             uint8_t encoding) :
                register_number(register_number),
                type(type),
                size(size),
                scale(scale),
                encoding(encoding) {
        }

        uint8_t register_number;
        IndexRegister::Type type;
        IndexRegister::Size size;
        IndexRegister::Scale scale;
        uint8_t encoding;
    };


    const encoding_test_params params[] = {
            // Register number
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00000000},
            {1, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00010000},
            {2, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00100000},
            {3, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00110000},
            {4, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b01000000},
            {5, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b01010000},
            {6, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b01100000},
            {7, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b01110000},

            // Register type
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00000000},
            {0, IndexRegister::Type::ADDRESS, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b10000000},

            // Size
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00000000},
            {0, IndexRegister::Type::DATA, IndexRegister::Size::LONG_WORD, IndexRegister::Scale::ONE, 0b00001000},

            // Scale
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::ONE, 0b00000000},
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::TWO, 0b00000010},
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::FOUR, 0b00000100},
            {0, IndexRegister::Type::DATA, IndexRegister::Size::WORD, IndexRegister::Scale::EIGHT, 0b00000110},
    };
}

class IndexRegisterNumberTest : public ::testing::TestWithParam<IndexRegister::Type> {
};

class IndexRegisterEncodingTest : public ::testing::TestWithParam<encoding_test_params> {
};

TEST_P(IndexRegisterNumberTest, ValidRegisterNumber) {
    std::array<const uint8_t, 8> numbers = {0, 1, 2, 3, 4, 5, 6, 7};

    for (auto number : numbers) {
        const IndexRegister::Type type = GetParam();
        IndexRegister reg(number, type, IndexRegister::Size::WORD, IndexRegister::Scale::ONE);
        EXPECT_EQ(number, reg.get_register_number());
    }
}

TEST_P(IndexRegisterEncodingTest, CorrectEncoding) {
    encoding_test_params params = GetParam();

    IndexRegister idx_reg(params.register_number, params.type, params.size, params.scale);
    EXPECT_EQ(params.encoding, idx_reg.encode());
}

TEST(IndexRegisterTest, GetProperties) {
    IndexRegister idx_register(1,
                                IndexRegister::Type::DATA,
                                IndexRegister::Size::LONG_WORD,
                                IndexRegister::Scale::FOUR);

    EXPECT_EQ(1, idx_register.get_register_number());
    EXPECT_EQ(IndexRegister::Type::DATA, idx_register.get_type());
    EXPECT_EQ(IndexRegister::Size::LONG_WORD, idx_register.get_size());
    EXPECT_EQ(IndexRegister::Scale::FOUR, idx_register.get_scale());
}

INSTANTIATE_TEST_CASE_P(IndexRegisterNumber, IndexRegisterNumberTest,
                        ::testing::Values(IndexRegister::Type::DATA, IndexRegister::Type::ADDRESS));

INSTANTIATE_TEST_CASE_P(IndexRegisterEncoding,
                        IndexRegisterEncodingTest,
                        ::testing::ValuesIn(params));

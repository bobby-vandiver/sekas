#include "gtest/gtest.h"
#include "operand/index_register.h"

class IndexRegisterNumberTest : public ::testing::TestWithParam<index_register::type> {
};

TEST_P(IndexRegisterNumberTest, ValidRegisterNumber) {
    std::array<const uint8_t, 8> numbers = {0, 1, 2, 3, 4, 5, 6, 7};

    for (auto number : numbers) {
        const index_register::type type = GetParam();
        index_register reg(number, type, index_register::size::WORD, index_register::scale::ONE);
        EXPECT_EQ(number, reg.get_register_number());
    }
}

INSTANTIATE_TEST_CASE_P(DataRegister, IndexRegisterNumberTest,
                        ::testing::Values(index_register::type::DATA, index_register::type::ADDRESS));

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
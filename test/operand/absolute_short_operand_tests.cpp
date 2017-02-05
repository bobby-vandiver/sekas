#include "gtest/gtest.h"
#include "operand/absolute_short_operand.h"

namespace {
    const uint16_t ADDRESS = 0xf00d;
}

class AbsoluteShortOperandTest : public ::testing::Test {
protected:
    AbsoluteShortOperandTest() : operand(ADDRESS) { }
    AbsoluteShortOperand operand;
};

TEST_F(AbsoluteShortOperandTest, GetModeField) {
    EXPECT_EQ(0b111, operand.get_mode_field());
}

TEST_F(AbsoluteShortOperandTest, GetRegisterField) {
    EXPECT_EQ(0b000, operand.get_register_field());
}

TEST_F(AbsoluteShortOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(1, operand.get_extension_word_count());
}

TEST_F(AbsoluteShortOperandTest, GetExtensionWordInvalid) {
    EXPECT_THROW({ operand.get_extension_word(1); }, std::invalid_argument);
}

TEST_F(AbsoluteShortOperandTest, GetExtensionWord) {
    EXPECT_EQ(ADDRESS, operand.get_extension_word(0));
}
#include "gtest/gtest.h"
#include "operand/absolute_long_operand.h"

namespace {
    const uint32_t ADDRESS = 0xbaadf00d;
    const uint16_t ADDRESS_HIGH = 0xbaad;
    const uint16_t ADDRESS_LOW = 0xf00d;
}

class AbsoluteLongOperandTest : public ::testing::Test {
protected:
    AbsoluteLongOperandTest() : operand(ADDRESS) { }
    AbsoluteLongOperand operand;
};

TEST_F(AbsoluteLongOperandTest, GetModeField) {
    EXPECT_EQ(0b111, operand.get_mode_field());
}

TEST_F(AbsoluteLongOperandTest, GetRegisterField) {
    EXPECT_EQ(0b001, operand.get_register_field());
}

TEST_F(AbsoluteLongOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(2, operand.get_extension_word_count());
}

TEST_F(AbsoluteLongOperandTest, GetExtensionWordInvalid) {
    EXPECT_THROW({ operand.get_extension_word(2); }, std::invalid_argument);
}

TEST_F(AbsoluteLongOperandTest, GetExtensionWord) {
    EXPECT_EQ(ADDRESS_HIGH, operand.get_extension_word(0));
    EXPECT_EQ(ADDRESS_LOW, operand.get_extension_word(1));
}
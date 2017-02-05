#include "gtest/gtest.h"
#include "operand/immediate_operand.h"

namespace {
    const uint16_t BYTE_DATA = 0xab;
    const uint16_t WORD_DATA = 0x2910;
    const uint32_t LONG_WORD_DATA = 0x12345678;
    const uint16_t LONG_WORD_DATA_HIGH = 0x1234;
    const uint16_t LONG_WORD_DATA_LOW = 0x5678;
}

class ImmediateOperandTest : public ::testing::Test {
protected:
    ImmediateOperandTest() :
            byte_operand(BYTE_DATA, ImmediateOperand::DataLength::BYTE),
            word_operand(WORD_DATA, ImmediateOperand::DataLength::WORD),
            long_word_operand(LONG_WORD_DATA, ImmediateOperand::DataLength::LONG_WORD) {
    }

    ImmediateOperand byte_operand;
    ImmediateOperand word_operand;
    ImmediateOperand long_word_operand;
};

TEST_F(ImmediateOperandTest, GetModeField) {
    EXPECT_EQ(0b111, byte_operand.get_mode_field());
    EXPECT_EQ(0b111, word_operand.get_mode_field());
    EXPECT_EQ(0b111, long_word_operand.get_mode_field());
}

TEST_F(ImmediateOperandTest, GetRegisterField) {
    EXPECT_EQ(0b100, byte_operand.get_register_field());
    EXPECT_EQ(0b100, word_operand.get_register_field());
    EXPECT_EQ(0b100, long_word_operand.get_register_field());
}

TEST_F(ImmediateOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(1, byte_operand.get_extension_word_count());
    EXPECT_EQ(1, word_operand.get_extension_word_count());
    EXPECT_EQ(2, long_word_operand.get_extension_word_count());
}

TEST_F(ImmediateOperandTest, GetExtensionWordInvalid) {
    EXPECT_THROW({ byte_operand.get_extension_word(1); }, std::invalid_argument);
    EXPECT_THROW({ word_operand.get_extension_word(1); }, std::invalid_argument);
    EXPECT_THROW({ long_word_operand.get_extension_word(2); }, std::invalid_argument);
}

TEST_F(ImmediateOperandTest, GetExtensionWord) {
    EXPECT_EQ(BYTE_DATA, byte_operand.get_extension_word(0));
    EXPECT_EQ(WORD_DATA, word_operand.get_extension_word(0));

    EXPECT_EQ(LONG_WORD_DATA_HIGH, long_word_operand.get_extension_word(0));
    EXPECT_EQ(LONG_WORD_DATA_LOW, long_word_operand.get_extension_word(1));
}


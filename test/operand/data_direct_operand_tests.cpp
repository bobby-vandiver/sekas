#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/data_direct_operand.h"

class DataDirectOperandTest : public ::testing::Test {
protected:
    DataDirectOperandTest() : operand(0) { }
    data_direct_operand operand;
};

template <>
operand::ptr create_with_register_number<data_direct_operand>(const uint8_t register_number) {
    return std::make_unique<data_direct_operand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(DataDirectOperand, OperandRegisterNumberTest, data_direct_operand);

TEST_F(DataDirectOperandTest, GetModeField) {
    EXPECT_EQ(0, operand.get_mode_field());
}

TEST_F(DataDirectOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(DataDirectOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}

#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/data_direct_operand.h"

class DataDirectOperandTest : public ::testing::Test {
protected:
    DataDirectOperandTest() : operand(0) { }
    DataDirectOperand operand;
};

template <>
std::unique_ptr<Operand> create_with_register_number<DataDirectOperand>(const uint8_t register_number) {
    return std::make_unique<DataDirectOperand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(DataDirectOperand, OperandRegisterNumberTest, DataDirectOperand);

TEST_F(DataDirectOperandTest, GetModeField) {
    EXPECT_EQ(0b000, operand.get_mode_field());
}

TEST_F(DataDirectOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(DataDirectOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}

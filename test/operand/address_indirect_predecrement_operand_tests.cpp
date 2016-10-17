#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_predecrement_operand.h"

class AddressIndirectPredecrementOperandTest : public ::testing::Test {
protected:
    AddressIndirectPredecrementOperandTest() : operand(0) { }
    AddressIndirectPredecrementOperand operand;
};

template <>
Operand::Ptr create_with_register_number<AddressIndirectPredecrementOperand>(const uint8_t register_number) {
    return std::make_unique<AddressIndirectPredecrementOperand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectPredecrement,
                              OperandRegisterNumberTest,
                              AddressIndirectPredecrementOperand);

TEST_F(AddressIndirectPredecrementOperandTest, GetModeField) {
    EXPECT_EQ(0b100, operand.get_mode_field());
}

TEST_F(AddressIndirectPredecrementOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressIndirectPredecrementOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}
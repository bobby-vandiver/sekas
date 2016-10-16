#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_operand.h"

class AddressIndirectOperandTest : public ::testing::Test {
protected:
    AddressIndirectOperandTest() : operand(0) { }
    address_indirect_operand operand;
};

template <>
operand::ptr create_with_register_number<address_indirect_operand>(const uint8_t register_number) {
    return std::make_unique<address_indirect_operand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectOperand, OperandRegisterNumberTest, address_indirect_operand);

TEST_F(AddressIndirectOperandTest, GetModeField) {
    EXPECT_EQ(2, operand.get_mode_field());
}

TEST_F(AddressIndirectOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressIndirectOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}

#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_postincrement_operand.h"

class AddressIndirectPostincrementOperandTest : public ::testing::Test {
protected:
    AddressIndirectPostincrementOperandTest() : operand(0) { }
    address_indirect_postincrement_operand operand;
};

template <>
operand::ptr create_with_register_number<address_indirect_postincrement_operand>(const uint8_t register_number) {
    return std::make_unique<address_indirect_postincrement_operand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectPostincrementOperand,
                              OperandRegisterNumberTest,
                              address_indirect_postincrement_operand);\

TEST_F(AddressIndirectPostincrementOperandTest, GetModeField) {
    EXPECT_EQ(0b011, operand.get_mode_field());
}

TEST_F(AddressIndirectPostincrementOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressIndirectPostincrementOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}

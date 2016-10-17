#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_postincrement_operand.h"

class AddressIndirectPostincrementOperandTest : public ::testing::Test {
protected:
    AddressIndirectPostincrementOperandTest() : operand(0) { }
    AddressIndirectPostincrementOperand operand;
};

template <>
Operand::Ptr create_with_register_number<AddressIndirectPostincrementOperand>(const uint8_t register_number) {
    return std::make_unique<AddressIndirectPostincrementOperand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectPostincrementOperand,
                              OperandRegisterNumberTest,
                              AddressIndirectPostincrementOperand);

TEST_F(AddressIndirectPostincrementOperandTest, GetModeField) {
    EXPECT_EQ(0b011, operand.get_mode_field());
}

TEST_F(AddressIndirectPostincrementOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressIndirectPostincrementOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}

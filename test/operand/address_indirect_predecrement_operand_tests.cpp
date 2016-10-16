#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_predecrement_operand.h"

class AddressIndirectPredecrementTest : public ::testing::Test {
protected:
    AddressIndirectPredecrementTest() : operand(0) { }
    address_indirect_predecrement_operand operand;
};

template <>
operand::ptr create_with_register_number<address_indirect_predecrement_operand>(const uint8_t register_number) {
    return std::make_unique<address_indirect_predecrement_operand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectPredecrement,
                              OperandRegisterNumberTest,
                              address_indirect_predecrement_operand);

TEST_F(AddressIndirectPredecrementTest, GetModeField) {
    EXPECT_EQ(4, operand.get_mode_field());
}

TEST_F(AddressIndirectPredecrementTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressIndirectPredecrementTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}
#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_direct_operand.h"

class AddressDirectOperandTest : public ::testing::Test {
protected:
    AddressDirectOperandTest() : operand(0) { }
    AddressDirectOperand operand;
};

template <>
std::unique_ptr<Operand> create_with_register_number<AddressDirectOperand>(const uint8_t register_number) {
    return std::make_unique<AddressDirectOperand>(register_number);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressDirectOperand, OperandRegisterNumberTest, AddressDirectOperand);

TEST_F(AddressDirectOperandTest, GetModeField) {
    EXPECT_EQ(0b001, operand.get_mode_field());
}

TEST_F(AddressDirectOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(0, operand.get_extension_word_count());
}

TEST_F(AddressDirectOperandTest, GetExtensionWord) {
    EXPECT_THROW({ operand.get_extension_word(0); }, std::invalid_argument);
}
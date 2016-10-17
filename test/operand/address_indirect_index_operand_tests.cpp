#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_index_operand.h"

namespace {
    const uint8_t DISPLACEMENT = 0xff;
}

class AddressIndirectIndexOperandTest : public ::testing::Test {
protected:
    AddressIndirectIndexOperandTest() : operand(0, DISPLACEMENT, nullptr) { }
    AddressIndirectIndexOperand operand;
};

template <>
Operand::Ptr create_with_register_number<AddressIndirectIndexOperand>(const uint8_t register_number) {
    return std::make_unique<AddressIndirectIndexOperand>(register_number, DISPLACEMENT, nullptr);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectIndexOperandTest,
                              OperandRegisterNumberTest,
                              AddressIndirectIndexOperand);

TEST_F(AddressIndirectIndexOperandTest, GetModeField) {
    EXPECT_EQ(0b110, operand.get_mode_field());
}

TEST_F(AddressIndirectIndexOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(1, operand.get_extension_word_count());
}

TEST_F(AddressIndirectIndexOperandTest, GetExtensionWordInvalid) {
    EXPECT_THROW({ operand.get_extension_word(1); }, std::invalid_argument);
}

TEST_F(AddressIndirectIndexOperandTest, GetExtensionWordDisplacement) {
    EXPECT_EQ(static_cast<uint16_t>(DISPLACEMENT), operand.get_extension_word(0) & 0xff);
}
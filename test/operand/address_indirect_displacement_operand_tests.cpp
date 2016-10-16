#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/address_indirect_displacement_operand.h"

namespace {
    const uint16_t DISPLACEMENT = 0xf00d;
}

class AddressIndirectDisplacementOperandTest : public ::testing::Test {
protected:
    AddressIndirectDisplacementOperandTest() : operand(0, DISPLACEMENT) { }
    address_indirect_displacement_operand operand;
};

template <>
operand::ptr create_with_register_number<address_indirect_displacement_operand>(const uint8_t register_number) {
    return std::make_unique<address_indirect_displacement_operand>(register_number, DISPLACEMENT);
}

INSTANTIATE_TYPED_TEST_CASE_P(AddressIndirectDisplacementOperandTest,
                              OperandRegisterNumberTest,
                              address_indirect_displacement_operand);

TEST_F(AddressIndirectDisplacementOperandTest, GetModeField) {
    EXPECT_EQ(0b101, operand.get_mode_field());
}

TEST_F(AddressIndirectDisplacementOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(1, operand.get_extension_word_count());
}

TEST_F(AddressIndirectDisplacementOperandTest, GetExtensionWord) {
    EXPECT_EQ(DISPLACEMENT, operand.get_extension_word(0));
    EXPECT_THROW({ operand.get_extension_word(1); }, std::invalid_argument);
}
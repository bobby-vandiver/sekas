#include "gtest/gtest.h"
#include "operand_tests.h"
#include "operand/pc_indirect_displacement_operand.h"

namespace {
    const int16_t SIGNED_DISPLACEMENT = -32768;
    const uint16_t UNSIGNED_DISPLACEMENT = 0x8000;
}

class ProgramCounterIndirectDisplacementOperandTest : public ::testing::Test {
protected:
    ProgramCounterIndirectDisplacementOperandTest() : operand(SIGNED_DISPLACEMENT) { }
    ProgramCounterIndirectDisplacementOperand operand;
};

TEST_F(ProgramCounterIndirectDisplacementOperandTest, GetModeField) {
    EXPECT_EQ(0b111, operand.get_mode_field());
}

TEST_F(ProgramCounterIndirectDisplacementOperandTest, GetRegisterField) {
    EXPECT_EQ(0b010, operand.get_register_field());
}

TEST_F(ProgramCounterIndirectDisplacementOperandTest, GetExtensionWordCount) {
    EXPECT_EQ(1, operand.get_extension_word_count());
}

TEST_F(ProgramCounterIndirectDisplacementOperandTest, GetExtensionWord) {
    EXPECT_EQ(UNSIGNED_DISPLACEMENT, operand.get_extension_word(0));
    EXPECT_THROW({ operand.get_extension_word(1); }, std::invalid_argument);
}
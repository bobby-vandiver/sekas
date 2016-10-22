#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mock_index_register.h"
#include "operand/pc_indirect_index_operand.h"

using ::testing::Return;

namespace {
    const uint8_t ENCODED_INDEX_REGISTER = 0xbe;

    const int8_t SIGNED_DISPLACEMENT = -3;
    const uint8_t UNSIGNED_DISPLACEMENT = 0xfd;
}

class ProgramCounterIndirectIndexOperandTest : public ::testing::Test {
protected:
    ProgramCounterIndirectIndexOperandTest() :
            mock_index_register(new MockIndexRegister()),
            operand(SIGNED_DISPLACEMENT, mock_index_register) {
    }

    MockIndexRegister *mock_index_register;
    ProgramCounterIndirectIndexOperand operand;
};

TEST_F(ProgramCounterIndirectIndexOperandTest, GetModeField) {
    EXPECT_EQ(0b111, operand.get_mode_field());
}

TEST_F(ProgramCounterIndirectIndexOperandTest, GetRegisterField) {
    EXPECT_EQ(0b011, operand.get_register_field());
}

TEST_F(ProgramCounterIndirectIndexOperandTest, GetExtensionWordInvalid) {
    EXPECT_THROW({ operand.get_extension_word(1); }, std::invalid_argument);
}

TEST_F(ProgramCounterIndirectIndexOperandTest, GetExtensionWordDisplacement) {
    EXPECT_CALL(*mock_index_register, encode());
    EXPECT_EQ(static_cast<uint16_t>(UNSIGNED_DISPLACEMENT), operand.get_extension_word(0) & 0xff);
}

TEST_F(ProgramCounterIndirectIndexOperandTest, GetExtensionWordIndexRegister) {
    EXPECT_CALL(*mock_index_register, encode())
            .WillOnce(Return(ENCODED_INDEX_REGISTER));

    EXPECT_EQ(static_cast<uint16_t>(ENCODED_INDEX_REGISTER) << 8, operand.get_extension_word(0) & 0xff00);
}
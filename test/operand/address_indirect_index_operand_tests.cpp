#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mock_index_register.h"
#include "operand_tests.h"
#include "operand/address_indirect_index_operand.h"

using ::testing::Return;

namespace {
    const uint8_t ENCODED_INDEX_REGISTER = 0xbe;
    const uint8_t DISPLACEMENT = 0xef;
}

class AddressIndirectIndexOperandTest : public ::testing::Test {
protected:
    AddressIndirectIndexOperandTest() :
            mock_index_register(new MockIndexRegister()),
            operand(0, DISPLACEMENT, mock_index_register) {
    }

    MockIndexRegister *mock_index_register;
    AddressIndirectIndexOperand operand;
};

template <>
std::unique_ptr<Operand> create_with_register_number<AddressIndirectIndexOperand>(const uint8_t register_number) {
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
    EXPECT_CALL(*mock_index_register, encode());
    EXPECT_EQ(static_cast<uint16_t>(DISPLACEMENT), operand.get_extension_word(0) & 0xff);
}

TEST_F(AddressIndirectIndexOperandTest, GetExtensionWordIndexRegister) {
    EXPECT_CALL(*mock_index_register, encode())
            .WillOnce(Return(ENCODED_INDEX_REGISTER));

    EXPECT_EQ(static_cast<uint16_t>(ENCODED_INDEX_REGISTER) << 8, operand.get_extension_word(0) & 0xff00);
}
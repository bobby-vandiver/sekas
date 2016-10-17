#ifndef SEKAS_OPERAND_TESTS_H
#define SEKAS_OPERAND_TESTS_H

#include "gtest/gtest.h"
#include "operand/operand.h"

#include <stdexcept>

template <typename T>
Operand::Ptr create_with_register_number(const uint8_t register_number);

template <typename T>
class OperandRegisterNumberTest : public ::testing::Test {
};

TYPED_TEST_CASE_P(OperandRegisterNumberTest);

TYPED_TEST_P(OperandRegisterNumberTest, ValidRegisterNumber) {
    std::array<const uint8_t, 8> numbers = {0, 1, 2, 3, 4, 5, 6, 7};

    for (auto number : numbers) {
        EXPECT_EQ(number, create_with_register_number<TypeParam>(number)->get_register_field());
    }
}

TYPED_TEST_P(OperandRegisterNumberTest, InvalidRegisterNumber) {
    EXPECT_THROW({ create_with_register_number<TypeParam>(8); }, std::invalid_argument);
}

REGISTER_TYPED_TEST_CASE_P(OperandRegisterNumberTest, ValidRegisterNumber, InvalidRegisterNumber);

#endif

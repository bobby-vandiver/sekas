#ifndef SEKAS_MOCK_INDEX_REGISTER_H
#define SEKAS_MOCK_INDEX_REGISTER_H

#include "gmock/gmock.h"
#include "operand/index_register.h"

class MockIndexRegister : public IndexRegister {
public:
    MOCK_CONST_METHOD0(encode, uint8_t());
};

#endif

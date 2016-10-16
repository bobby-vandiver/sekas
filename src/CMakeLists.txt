project(libsekas)

include_directories(../include/operand)

set(OPERAND_SOURCES
        operand/operand_validation.cpp
        operand/data_direct_operand.cpp
        operand/address_direct_operand.cpp
        operand/address_indirect_operand.cpp
        operand/address_indirect_postincrement_operand.cpp
        operand/address_indirect_predecrement_operand.cpp
        operand/address_indirect_displacement_operand.cpp)

add_library(libsekas STATIC ${OPERAND_SOURCES})

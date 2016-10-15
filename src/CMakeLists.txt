project(libsekas)

include_directories(../include/operand)

set(OPERAND_SOURCES operand/data_direct_operand.cpp operand/address_direct_operand.cpp operand/operand_validation.cpp)

add_library(libsekas STATIC ${OPERAND_SOURCES})

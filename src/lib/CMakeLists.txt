project(sekas_library)

################################
# SEKAS Library
################################
# Compiled as a library to facilitate testing.
################################

include_directories(include/symbol include/exception include/operand)

set(symbolSources symbol/Symbol.cpp symbol/SymbolTable.cpp)

set(operandSources
		operand/OperandFactory.cpp
		operand/OperandUtils.cpp
		operand/DataRegisterDirectOperand.cpp
		operand/AddressRegisterDirectOperand.cpp
		operand/AddressRegisterIndirectOperand.cpp
		operand/AddressRegisterIndirectPostIncrementOperand.cpp
		operand/AddressRegisterIndirectPreDecrementOperand.cpp)

set(sources ${symbolSources} ${operandSources})

add_library(${PROJECT_NAME} ${sources})

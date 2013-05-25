project(sekas_library)

################################
# SEKAS Library
################################
# Compiled as a library to facilitate testing.
################################

include_directories(include/symbol include/exception include/operand)

set(symbolSources Symbol/Symbol.cpp Symbol/SymbolTable.cpp)
set(operandSources Operand/OperandFactory.cpp Operand/OperandUtils.cpp Operand/DataRegisterDirectOperand.cpp)

set(sources ${symbolSources} ${operandSources})

add_library(${PROJECT_NAME} ${sources})

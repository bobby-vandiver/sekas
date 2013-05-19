project(sekas_library)

################################
# SEKAS Library
################################
# Compiled as a library to facilitate testing.
################################

include_directories(include)
set(sources Symbol.cpp SymbolTable.cpp OperandFactory.cpp)

add_library(${PROJECT_NAME} ${sources})

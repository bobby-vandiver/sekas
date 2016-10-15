project(libsekas)

include_directories(../include/operand)
add_library(libsekas STATIC operand/data_direct_operand.cpp)

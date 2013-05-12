project(sekas_library)

################################
# SEKAS Library
################################
# Compiled as a library to facilitate testing.
################################

add_library(${PROJECT_NAME} include/simple.h simple.cpp)

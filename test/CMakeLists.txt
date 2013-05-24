cmake_minimum_required(VERSION 2.8.4)
project(tests)

################################
# SEKAS Project Production Files
################################

include_directories(${sekas_SOURCE_DIR}/sekas_library)

################################
# GMock and GTest
################################
add_subdirectory(gmock-1.6.0)
enable_testing()
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

################################
# Unit Tests
################################

include_directories(${sekas_library_SOURCE_DIR}/include ${sekas_library_SOURCE_DIR})

set(sources TestRunner.cpp SymbolTests.cpp SymbolTableTests.cpp OperandFactoryTests.cpp OperandUtilsTests.cpp DataRegisterDirectOperandTests.cpp)

add_executable(unit_tests ${sources})

target_link_libraries(unit_tests sekas_library)
target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests gmock gmock_main)

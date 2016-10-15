project(tests)

include_directories(../include)
add_subdirectory(lib)

include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(OPERAND_TESTS operand/data_direct_operand_tests.cpp operand/address_direct_operand_tests.cpp)

add_executable(unit_tests ${OPERAND_TESTS})

target_link_libraries(unit_tests libsekas)
target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests gmock gmock_main)
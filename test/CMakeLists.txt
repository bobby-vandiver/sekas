project(tests)

add_subdirectory(lib)

include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(basic_check_tests basic/basic_check.cpp)

add_executable(unit_tests ${basic_check_tests})

target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests gmock gmock_main)
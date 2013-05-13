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

set(unit_test_sources
	unit/TestRunner.cpp
	unit/SymbolTests.cpp
)

add_executable(unit_tests
	${unit_test_sources})

target_link_libraries(unit_tests sekas_library)
target_link_libraries(unit_tests gtest gtest_main)

add_test(all_unit_tests unit_tests)
add_custom_target(run_unit_tests COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS unit_tests)
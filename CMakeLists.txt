cmake_minimum_required(VERSION 3.5)
project(sekas)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++14")
endif()

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)

add_executable(sekas main.cpp)
target_link_libraries(sekas libsekas)
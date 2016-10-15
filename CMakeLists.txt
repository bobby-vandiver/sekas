cmake_minimum_required(VERSION 3.5)
project(sekas)

add_definitions(-std=c++1y)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)

add_executable(sekas main.cpp)
target_link_libraries(sekas libsekas)
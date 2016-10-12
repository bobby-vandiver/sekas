cmake_minimum_required(VERSION 3.5)
project(sekas)

add_definitions(-std=c++11)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)

set(SOURCE_FILES main.cpp)
add_executable(sekas ${SOURCE_FILES})

target_link_libraries(sekas libsekas)
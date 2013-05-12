project(executable)

################################
# Executable
################################

# include_directories(${CMAKE_SOURCE_DIR}/src)
# link_directories(${CMAKE_BINARY_DIR}/src)

include_directories(${sekas_library_SOURCE_DIR}/include ${sekas_library_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} sekas_library)
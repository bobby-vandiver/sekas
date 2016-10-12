project(libsekas)

set(HEADER_FILES adder.h)
set(SOURCE_FILES adder.cpp)

add_library(libsekas STATIC ${SOURCE_FILES} ${HEADER_FILES})
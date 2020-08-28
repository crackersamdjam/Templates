cmake_minimum_required(VERSION 3.16)
project(templates)

set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=undefined -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-stack_size -Wl,40000000")
set(CMAKE_CXX_STANDARD 17)

add_executable(templates test.cpp)
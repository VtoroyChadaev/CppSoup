#cmake_minimum_required(VERSION 3.30)

#project(lab1_tests)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


# add_library(vec_lib "../src/vector/vector.hpp" "../src/vector/vector.cpp")

add_executable(tests_program tests.cpp)
target_link_libraries(tests_program vec_lib)


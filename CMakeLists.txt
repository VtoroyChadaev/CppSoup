cmake_minimum_required(VERSION 3.30)
project(oop_lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_compile_options(--coverage)
add_link_options(--coverage -lgtest -lgmock)

add_subdirectory("src/vector")
add_subdirectory("src/input")
add_subdirectory(tests)

add_executable(program "src/main.cpp")

target_link_libraries(program vec_lib inp_lib)

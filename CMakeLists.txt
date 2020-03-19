cmake_minimum_required(VERSION 3.15)
project(ast)

set(CMAKE_CXX_STANDARD 17)

add_executable(ast main.cpp state_machine.cpp)

add_executable(test test_ast.cpp state_machine.cpp)
cmake_minimum_required(VERSION 3.18)
project(PS4 C)

set(CMAKE_C_STANDARD 99)

add_executable(PS4 main.c stack.c stack.h rpn.c rpn.h errors.h rpn-convert.c rpn-convert.h node.c node.h)

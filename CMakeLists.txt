cmake_minimum_required(VERSION 3.27)
project(datacopy_ipc_win C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-ansi -pedantic-errors -std=c11 -Wall -Wextra)

add_executable(receiver receiver.c shared.c)
add_executable(sender sender.c shared.c)

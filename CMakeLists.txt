cmake_minimum_required(VERSION 3.20.0)

set(BOARD_ROOT ${CMAKE_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(myboardapp)

target_sources(app PRIVATE src/main.c)

file(WRITE ${CMAKE_SOURCE_DIR}/.clangd
"CompileFlags:
    CompilationDatabase: ${CMAKE_CURRENT_BINARY_DIR}
")

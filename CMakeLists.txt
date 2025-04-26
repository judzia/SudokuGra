cmake_minimum_required(VERSION 3.31)
project(SudokuGra C)

set(CMAKE_C_STANDARD 11)

add_executable(SudokuGra
        main.c
        sudoku.c)

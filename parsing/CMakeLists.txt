cmake_minimum_required(VERSION 3.28)
project(mysh C)

target_compile_definitions(
        minishell.c
        minishell.h
        lib_utils.c
)
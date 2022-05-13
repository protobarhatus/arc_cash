cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)

set(TYPES_AND_FUNCS         type_declaration.c
        type_declaration.h
        arithmetic_type_declaration.c
        arithmetic_type_declaration.h
        functions_extensions.c
        functions_extensions.h
        general_type.c
        general_type.h
        complete_type_container.c
        complete_type_container.h
        io_type_declaration.c
        io_type_declaration.h)

list(TRANSFORM TYPES_AND_FUNCS PREPEND types_and_functions_declarations/)
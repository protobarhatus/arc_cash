cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)

set(LINEAR_ALGEBRA
        matrix.h
        matrix_def.h
        vector_algebraic_addendum.h
        vector_algebraic_addendum_def.h
        vector_algebraic_addendum_general_type.h
        vector_algebraic_addendum_general_type.c
        rational.c
        rational.h
        complex.c
        complex.h
        matrix_general_type.h
        matrix_general_type.c)

list(TRANSFORM LINEAR_ALGEBRA PREPEND linear_algebra_elements/)
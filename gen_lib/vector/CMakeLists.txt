cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 99)

#add_library(Vector STATIC Vector.c Vector.h vectordef.c vectordef.h vectorfuncs.c vectorfuncs.h)
set(VECTOR arrayint.c
        arrayint.h
        Array2dInt.c
        Array2dInt.h
        vector.c
        vector.h
        algorithms.c
        algorithms.h
        sparse_vector.c
        sparse_vector.h
        vector_general_type.c
        vector_general_type.h
        vector_def.h
)

list(TRANSFORM VECTOR PREPEND vector/)

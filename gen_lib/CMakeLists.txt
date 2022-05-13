cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)

#include_directories(gen_lib/user_interacts)
#include_directories(gen_lib/standart_classes)
#include_directories(gen_lib/types_and_functions_declarations)
#include_directories(gen_lib/linear_algebra_elements)
#include_directories(gen_lib/graph_work)
#include_directories(gen_lib/vector)

include(gen_lib/linear_algebra_elements/CMakeLists.txt)
include(gen_lib/types_and_functions_declarations/CMakeLists.txt)
include(gen_lib/user_interacts/CMakeLists.txt)
include(gen_lib/vector/CMakeLists.txt)
include(gen_lib/standart_classes/CMakeLists.txt)
include(gen_lib/graph_work/CMakeLists.txt)


list(TRANSFORM VECTOR PREPEND gen_lib/)
list(TRANSFORM TYPES_AND_FUNCS PREPEND gen_lib/)
list(TRANSFORM USER_INTERACTIONS PREPEND gen_lib/)
list(TRANSFORM LINEAR_ALGEBRA PREPEND gen_lib/)
list(TRANSFORM STANDART_CLASSES PREPEND gen_lib/)
list(TRANSFORM NSTD_CLASSES PREPEND gen_lib/)
set(LIB ${VECTOR} ${TYPES_AND_FUNCS} ${USER_INTERACTIONS} ${LINEAR_ALGEBRA} ${STANDART_CLASSES} ${NSTD_CLASSES})


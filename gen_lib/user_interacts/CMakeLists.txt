cmake_minimum_required(VERSION 3.16)
project(fibonachy_nim C)

set(CMAKE_C_STANDARD 99)

set(USER_INTERACTIONS user_interactions.h user_interactions.c )

list(TRANSFORM USER_INTERACTIONS PREPEND user_interacts/)
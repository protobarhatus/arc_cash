cmake_minimum_required(VERSION 3.16)
project(ARC C)



set(CMAKE_C_STANDARD 99)
include_directories(gen_lib)
include_directories(standart_classes)

include(gen_lib/CMakeLists.txt)
message(${LIB})
add_executable(ARC main.c ${LIB} arc_cache.c arc_cache.h Page.c Page.h cachedir.h cachedir.c AutoChecker.c AutoChecker.h fcr_cache.c fcr_cache.h)

target_link_libraries(ARC m)
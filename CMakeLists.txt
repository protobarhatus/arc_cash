cmake_minimum_required(VERSION 3.16)
project(ARC C)

set(CMAKE_C_STANDARD 99)
include_directories(gen_lib)
include_directories(standart_classes)

include(gen_lib/CMakeLists.txt)
add_executable(ARC ${LIB} arc_main.c arc_cache.c arc_cache.h Page.c Page.h cachedir.h cachedir.c AutoChecker.c AutoChecker.h)
add_executable(LRU ${LIB} lru_main.c lru_cache.c lru_cache.h Page.c Page.h)
add_executable(FRC ${LIB} frc_main.c fcr_cache.c fcr_cache.h Page.c Page.h cachedir.h cachedir.c AutoChecker.c Autochecker.h)
add_executable(testgen ${LIB} testgen_main.c testgen.c testgen.h test_idents.h)
add_executable(test ${LIB} cachetest_main.c cachetest.c cachetest.h test_idents.h)

target_link_libraries(ARC m)
target_link_libraries(LRU m)
target_link_libraries(FRC m)
target_link_libraries(testgen m)
target_link_libraries(test m)

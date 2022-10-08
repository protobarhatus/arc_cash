cmake_minimum_required(VERSION 3.16)
project(ARC C)

set(CMAKE_C_STANDARD 99)
include_directories(gen_lib)
include_directories(standart_classes)

include(gen_lib/CMakeLists.txt)
add_executable(arc ${LIB} arc_src/arc_main.c frc_src/frc_cache.c frc_src/frc_cache.h arc_src/arc_cache.c arc_src/arc_cache.h shared/Page/Page.c shared/Page/Page.h shared/cachedir/cachedir.h shared/cachedir/cachedir.c shared/AutoChecker/AutoChecker.c shared/AutoChecker/AutoChecker.h)
add_executable(lru ${LIB} lru_src/lru_main.c lru_src/lru_cache.c lru_src/lru_cache.h shared/Page/Page.c shared/Page/Page.h)
add_executable(frc ${LIB} frc_src/frc_main.c frc_src/frc_cache.c frc_src/frc_cache.h arc_src/arc_cache.c arc_src/arc_cache.h shared/Page/Page.c shared/Page/Page.h shared/cachedir/cachedir.h shared/cachedir/cachedir.c shared/AutoChecker/AutoChecker.c shared/AutoChecker/AutoChecker.h)
add_executable(testgen ${LIB} testsys/testgen/testgen_main.c testsys/testgen/testgen.c testsys/testgen/testgen.h testsys/test_idents.h)
add_executable(test ${LIB} testsys/cachetest/cachetest_main.c testsys/cachetest/cachetest.c testsys/cachetest/cachetest.h testsys/test_idents.h)

target_link_libraries(arc m)
target_link_libraries(lru m)
target_link_libraries(frc m)
target_link_libraries(testgen m)
target_link_libraries(test m)

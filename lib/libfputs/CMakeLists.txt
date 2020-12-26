cmake_minimum_required(VERSION 3.17)
project(libfputs C)

set(CMAKE_C_STANDARD 99)
include_directories(include)

set(SOURCES
    src/linkedlist.c
    src/set.c
    src/stack.c
    src/binarytree.c
)

add_library(libfputs ${SOURCES})

if(${CMAKE_PROJECT_NAME} STREQUAL libfputs)
    add_executable(tests tests/tests.c)
    target_include_directories(tests PRIVATE include)
    target_link_libraries(tests libfputs)
endif()


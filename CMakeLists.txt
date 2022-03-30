cmake_minimum_required(VERSION 3.16)
project(derelict C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/libflint)
add_subdirectory(lib/flecs)

FILE(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

set(SRC
    src/main.c
    src/gamestate.c
    src/colors.c

    src/ecs/components.c
    src/ecs/systems.c

    src/mapping/map.c
    src/mapping/gen_utility.c
    src/mapping/generators/test.c

    src/screens/manager.c
    src/screens/mainmenu.c
    src/screens/gamescreen.c
    src/screens/utility.c
)

add_executable(derelict ${SRC})

target_include_directories(derelict PRIVATE
    include
    lib/libflint/include
    lib/flecs/include
    lib/uthash/include
)

target_link_directories(derelict PRIVATE
    lib
)

target_link_libraries(derelict PRIVATE
    BearLibTerminal
    flint
    flecs
    bsd
    sodium
)
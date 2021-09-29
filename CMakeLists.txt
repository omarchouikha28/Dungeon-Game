# cmake_minimum_required(VERSION <specify CMake version here>)
project(01_dungeon C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(01_dungeon
        dungeon.c
        dungeon.h dungeon_setup.c dungeon_setup.h dungeon_player_controls.c dungeon_player_controls.h libs.h monster.c monster.h)

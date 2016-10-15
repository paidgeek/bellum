cmake_minimum_required(VERSION 3.6)
project(bellum)

file(GLOB GAME_SOURCES src/*.cc src/*.h)
add_executable(game ${GAME_SOURCES})

include_directories(../../src/core/include)
target_link_libraries(game core)

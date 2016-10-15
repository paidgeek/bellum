cmake_minimum_required(VERSION 3.6)
project(bellum)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CORE_SOURCES src/*.cc src/*.h)
add_library(core SHARED ${CORE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

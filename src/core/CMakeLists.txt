cmake_minimum_required(VERSION 3.6)
project(bellum)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE CORE_SOURCES src/**.cc src/**.h)
add_library(core SHARED ${CORE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

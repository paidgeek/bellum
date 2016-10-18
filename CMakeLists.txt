cmake_minimum_required(VERSION 3.6)
project(bellum)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
include(cmake/add_sources.cmake)

# Boost
FIND_PACKAGE (Boost REQUIRED COMPONENTS
    log_setup
    thread
    date_time
    filesystem
    system
    program_options)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# GLFW
add_subdirectory(third_party/glew)
include_directories(third_party/glfw/include)
include_directories(third_party/glew/include)

find_path(OPENGL_INCLUDE_DIR GL/gl.h)
find_library(OPENGL_gl_LIBRARY opengl32)
find_library(OPENGL_glu_LIBRARY glu32)

add_subdirectory(engine)
include_directories(engine)

add_subdirectory(bellum)

add_executable(bellum ${SRCS})

if(WIN32)
  link_directories(third_party/glfw/lib/mingw)
endif()

target_link_libraries(bellum
    glfw3
    ${Boost_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY})

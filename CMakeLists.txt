cmake_minimum_required(VERSION 3.6)
project(bellum)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

add_subdirectory(third_party/glew)

file(GLOB SOURCE_FILES src/*.cc)
source_group("src" FILES ${SOURCE_FILES})
source_group("third_party/glew/src" FILES ${GLEW_SRCS})
source_group("third_party/glew/include/GL" FILES ${GLEW_HEADERS})

add_executable(bellum
    ${SOURCE_FILES}
    ${GLEW_SRCS}
    ${GLEW_HEADERS})

include_directories("third_party/glfw/include")
include_directories("third_party/glew/include")

link_directories(third_party/glfw/lib/mingw)

FIND_PATH(OPENGL_INCLUDE_DIR GL/gl.h )
FIND_LIBRARY(OPENGL_gl_LIBRARY opengl32 )
FIND_LIBRARY(OPENGL_glu_LIBRARY glu32 )

target_link_libraries(bellum glfw3 ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

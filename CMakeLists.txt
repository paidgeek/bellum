cmake_minimum_required(VERSION 3.6)
project(bellum)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
include(cmake/add_sources.cmake)

# GLFW
add_definitions(-DGLEW_STATIC)
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

if (WIN32)
  link_directories(third_party/glfw/lib/mingw)
endif ()

target_link_libraries(bellum
  glfw3
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY})

# Copy assets
#add_custom_command(TARGET bellum POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_directory
#  ${CMAKE_SOURCE_DIR}/assets
#  $<TARGET_FILE_DIR:bellum>/assets)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

cmake_minimum_required(VERSION 3.26)

project(gllearn)

add_subdirectory(lib/glfw-3.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)  # For C++17

add_definitions(-DSHADERS_DIR="${CMAKE_SOURCE_DIR}/shaders")

include_directories(
  headers
  src
  glad
  lib/glfw-3.4/include
)

file(GLOB PROJECT_SHADERS Glitter/Shaders/*.comp
  Glitter/Shaders/*.frag
  Glitter/Shaders/*.geom
  Glitter/Shaders/*.vert)

source_group("shaders" FILES ${PROJECT_SHADERS})

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
  glad/glad.c
  headers/glad.h
  headers/glfw3.h
  headers/glfw3native.h
  headers/khrplatform.h
  ${PROJECT_SHADERS}
)

target_link_libraries(
  ${PROJECT_NAME}
  glfw ${GLFW_LIBRARIES}
  ${GLAD_LIBRARIES}
)
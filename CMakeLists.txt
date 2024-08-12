cmake_minimum_required(VERSION 3.26)

project(gllearn)

add_subdirectory(lib/glfw-3.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    headers
    src
    glad
    lib/glfw-3.4/include
)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    glad/glad.c
    headers/glad.h
    headers/glfw3.h
    headers/glfw3native.h
    headers/khrplatform.h
)

target_link_libraries(
    ${PROJECT_NAME}
    glfw ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
)
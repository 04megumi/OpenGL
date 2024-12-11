cmake_minimum_required(VERSION 3.10)

project(OpenGL_App)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/glfw lib/glm )
add_subdirectory(lib/assimp)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/assimp/include
    ${CMAKE_SOURCE_DIR}/lib/glut/include
    ${CMAKE_SOURCE_DIR}/head
)

add_executable(OpenGL_App  test.cpp  lib/glad/src/glad.c src/Shader.cpp src/Vertices.cpp src/Matrix.cpp src/Window.cpp src/Bezier.cpp src/Model.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib/glut/lib)

target_link_libraries(OpenGL_App
    "-framework OpenGL"
    glfw
    assimp
    ${CMAKE_SOURCE_DIR}/lib/glut/lib/libglut.dylib
)
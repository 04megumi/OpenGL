cmake_minimum_required(VERSION 3.10)

project(OpenGL_Project)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 包含 GLFW 子目录
add_subdirectory(lib/glfw)

# 添加头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/lib/glfw/include
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/lib/glm/include
    ${CMAKE_SOURCE_DIR}/head
)

# 查找线程库
find_package(Threads REQUIRED)

# 创建可执行文件
add_executable(OpenGL_App 
    source/exp1.3.cpp 
    source/Shader.cpp 
    lib/glad/src/glad.c  # GLAD 的源文件
)

# 链接库和框架
target_link_libraries(OpenGL_App PRIVATE 
    glfw               # GLFW
    Threads::Threads   # 线程库
    "-framework OpenGL" # OpenGL 框架
)
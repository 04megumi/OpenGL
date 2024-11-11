cmake_minimum_required(VERSION 3.10)

project(OpenGL_Project)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 添加 GLFW 和 GLAD 的头文件路径
include_directories(
    /opt/homebrew/include           # GLFW 头文件路径
    /opt/homebrew/Cellar/glad/include # GLAD 头文件路径
)

# 创建可执行文件
add_executable(OpenGL_App src/main.cpp)

# 手动链接 GLFW 和 GLAD 库
target_link_libraries(OpenGL_App
    /opt/homebrew/lib/libglfw.dylib  # GLFW 动态库
    /opt/homebrew/Cellar/glad/lib/libglad.a  # GLAD 静态库
)

# 链接 OpenGL 框架
target_link_libraries(OpenGL_App "-framework OpenGL")
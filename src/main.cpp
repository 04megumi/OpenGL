#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{

    // GLFW初始化 (3.3版本, 核心模式OpenGL)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "DwawCube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 使用glad导入glfw函数地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window); //交换缓冲
        glfwPollEvents(); //检查有没有触发事件
    }

    glfwTerminate();

    return 0;
}
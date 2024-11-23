/*
    实验内容： 绘制贝塞尔曲线
*/




#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"



// 矩阵变换时，需要用到的六个矩阵
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 transltation = glm::mat4(1.0f);
glm::mat4 rotation = glm::mat4(1.0f);
glm::mat4 scale = glm::mat4(1.0f);
glm::mat4 groundModel = glm::mat4(1.0f);


// 一些向量
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); //相机位置
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);  //相机看相的位置
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);  //相机上向量，需要标准化



// 一些全局变量
Shader ourShader;
bool shouldDrawLine = false;
float lastX = 10000, lastY = 10000;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float cameraSpeed = 0.05f;


int main()
{

    // GLFW初始化 (3.3版本, 核心模式OpenGL)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "exp1.5", NULL, NULL);
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

    ourShader = Shader("shader/vectorShader(1.5).txt", "shader/fragmentShader(1.5).txt");
    ourShader.use();
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);
    ourShader.setMat4("model", model);


    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {                                                                   
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();


    return 0;
}
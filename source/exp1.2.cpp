/*
    实验内容： 绘制立方体
*/




#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"


const unsigned int SCR_WIDTH = 800; 
const unsigned int SCR_HEIGHT = 600; 


int main()
{


    // GLFW初始化 (3.3版本, 核心模式OpenGL)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "exp1.2", NULL, NULL);
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


    Shader ourShader("shader/vectorShader.txt", "shader/fragmentShader.txt");


    // 定义顶点，每行一个，前三个是坐标，后三个是rgb
    float cubeVertices[] = 
    {
        -0.5f, -0.5f, -3.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -3.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -3.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -2.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -2.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -2.5f, 1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -2.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -2.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -2.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -2.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -2.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -3.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, 0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -3.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -2.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -2.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -3.5f, 0.0f, 1.0f, 0.0f,
    };


    unsigned int VBO, VAO; //Vertex Array（Buffer） Object，
    glGenVertexArrays(1, &VAO); //给VAO分配内存
    glGenBuffers(1, &VBO); //给VBO分配内存
    glBindVertexArray(VAO); //绑定VertexArray为VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //绑定GL_ARRAY_BUFFER为VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW); //把cubevertices写入VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    // 激活着色器
    ourShader.use();


    // 创建透视变换矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // 摄像机向后移动
    ourShader.setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f); 
    ourShader.setMat4("model", model);


    // 开启深度测试
    glEnable(GL_DEPTH_TEST);


    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window); //交换缓冲
        glfwPollEvents(); //检查有没有触发事件
    }


    glfwTerminate();

    
    return 0;
}
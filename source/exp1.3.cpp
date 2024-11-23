/*
    实验内容： 图形几何变换
*/




#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"


enum TransMode
{
    Translate,
    Rotate,
    Scale
};
TransMode transModeSelected = Rotate;


// 矩阵变换时，需要用到的六个矩阵
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 transltation = glm::mat4(1.0f);
glm::mat4 rotation = glm::mat4(1.0f);
glm::mat4 scale = glm::mat4(1.0f);


// 一些全局变量
Shader ourShader;
bool shouldDrawLine = false;
float lastX = 10000, lastY = 10000;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// 键鼠函数
void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // 按Esc退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 按0重置变换
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        transltation = glm::mat4(1.0f);
        rotation = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        ourShader.setMat4("model", model); // 更新着色器
    }

    // 按1切换填充/线框模式
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        shouldDrawLine = !shouldDrawLine;
        if (shouldDrawLine)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置为线框模式
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 设置为填充模式
    }

    // 按R开启旋转模式
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        transModeSelected = Rotate;

    // 按T开启平移模式
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        transModeSelected = Translate;

    // 按S开启缩放模式
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        transModeSelected = Scale;
}
void mouseCallBack(GLFWwindow *window, double xpos, double ypos)
{
    // 当鼠标左键被按住时
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        // 检查是否是第一次按下鼠标
        if (lastX > SCR_WIDTH)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }

        // 计算鼠标移动的偏移量
        float deltaX = xpos - lastX;
        float deltaY = ypos - lastY;

        if (transModeSelected == Translate)
        {
            // 鼠标移动控制平移
            transltation = glm::translate(transltation, glm::vec3(deltaX / 100.0f, -deltaY / 100.0f, 0.0f));
        }
        else if (transModeSelected == Rotate)
        {
            // 鼠标移动控制旋转
            rotation = glm::rotate(rotation, glm::radians(deltaX / 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            rotation = glm::rotate(rotation, glm::radians(deltaY / 5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (transModeSelected == Scale)
        {
            // 鼠标移动控制缩放
            float scaleFactor = 1.0f + deltaY / 100.0f;
            scale = glm::scale(scale, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
        }

        // 更新最终的模型矩阵
        model = transltation * rotation * scale;
        ourShader.setMat4("model", model); // 更新着色器的model矩阵

        // 更新鼠标的最后位置
        lastX = xpos;
        lastY = ypos;
    }
    else
    {
        // 鼠标左键没有被按下，将上一帧位置无效化
        lastX = 10000;
    }
}


int main()
{


    // GLFW初始化 (3.3版本, 核心模式OpenGL)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "exp1.3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // 把window绑定键盘函数和鼠标
    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetCursorPosCallback(window, mouseCallBack);


    // 使用glad导入glfw函数地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }


    ourShader = Shader("shader/vectorShader.txt", "shader/fragmentShader.txt");


    // 定义顶点，每行一个，前三个是坐标，后三个是rgb
    float vertices[] = 
    {
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    };


    unsigned int VBO, VAO; //Vertex Array（Buffer） Object，
    glGenVertexArrays(1, &VAO); //给VAO分配内存
    glGenBuffers(1, &VBO); //给VBO分配内存
    glBindVertexArray(VAO); //绑定VertexArray为VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //绑定GL_ARRAY_BUFFER为VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把cubevertices写入VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    ourShader.use();
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("view", view);
    ourShader.setMat4("model", model);


    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        model = transltation * rotation *scale;
        ourShader.setMat4("model", model);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window); //交换缓冲
        glfwPollEvents(); //检查有没有触发事件
    }


    glfwTerminate();


    return 0;
}
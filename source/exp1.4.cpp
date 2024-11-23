/*
    实验内容： 图形观察变换，五视图
*/




#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Transform.h"

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

    // 按Y开启缩放模式
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        transModeSelected = Scale;
    
    // 按W相机向前移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        cameraPosition += cameraSpeed * cameraFront;
        cameraTarget += cameraSpeed *cameraFront;
    }

    // 按S相机向前移动
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        cameraPosition -= cameraSpeed * cameraFront;
        cameraTarget -= cameraSpeed *cameraFront;
    }

    // 按D相机向右移动
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPosition += cameraSpeed * cameraRight;
        cameraTarget += cameraSpeed *cameraRight;
    }

    // 按A相机向左移动
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPosition -= cameraSpeed * cameraRight;
        cameraTarget -= cameraSpeed *cameraRight;
    }

    // 按Q相机向上移动
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cameraPosition += cameraSpeed * cameraUp;
        cameraTarget += cameraSpeed *cameraUp;
    }

    // 按E相机向下移动
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cameraPosition -= cameraSpeed * cameraUp;
        cameraTarget -= cameraSpeed *cameraUp;
    }

    // 按2开启前视图
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
    }

    // 按3开启后视图
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, 0.0f, 3.0f);     
    }

    // 按4开启左视图
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(-3.0f, 0.0f, 0.0f);  
    }

    // 按5开启右视图
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        cameraTarget = glm::vec3(3.0f, 0.0f, 0.0f);
    }

    // 按6开启顶视图
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, -3.0f, 0.0f);  
    }

    // 按7开启底视图
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 3.0f, -2.99f);
        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    }      
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
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        if (lastX > SCR_WIDTH)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }

        // 计算鼠标偏移
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // 注意 Y 轴是反的
        lastX = xpos;
        lastY = ypos;

        // 根据灵敏度调整偏移
        xoffset *= cameraSpeed;
        yoffset *= cameraSpeed;

        // 计算水平和垂直旋转
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);

        // 水平旋转：绕 cameraUp 轴
        glm::mat4 rotationHorizontal = glm::rotate(glm::mat4(1.0f), glm::radians(-xoffset), cameraUp);
        glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));

        // 垂直旋转：绕 right 轴
        glm::mat4 rotationVertical = glm::rotate(glm::mat4(1.0f), glm::radians(-yoffset), right);

        // 计算新的前方向
        glm::vec4 newFront = rotationHorizontal * rotationVertical * glm::vec4(cameraFront, 1.0f);
        cameraFront = glm::normalize(glm::vec3(newFront));

        // 更新 cameraTarget 和 view 矩阵
        cameraTarget = cameraPosition + cameraFront;
        view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

        // 更新着色器中的 view 矩阵
        ourShader.setMat4("view", view);
    }
    else
    {
        // 鼠标没有被按下，将上一帧位置无效化
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
    GLFWwindow *window = glfwCreateWindow(800, 600, "exp1.4", NULL, NULL);
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

        -1.0f, 0.0f, -1.0f, 0.5f, 0.5f, 0.5f,
        1.0f, 0.0f, -1.0f, 0.5f, 0.5f, 0.5f,
        1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
        1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
        -1.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f,
        -1.0f, 0.0f, -1.0f, 0.5f, 0.5f, 0.5f
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
        view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        ourShader.setMat4("view", view);

        model = transltation * rotation * scale;                                                                               

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ourShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        groundModel = glm::translate(model, glm::vec3(0, -0.5, 0));
        ourShader.setMat4("model", groundModel);
        glDrawArrays(GL_TRIANGLES, 36, 6);

        glfwSwapBuffers(window); //交换缓冲
        glfwPollEvents(); //检查有没有触发事件
    }


    glfwTerminate();


    return 0;
}
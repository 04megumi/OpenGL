#include "Window.h"

Window::Window(int w, int h, const char *title) : width(w), height(h), matrix(this), bezier(10, 1)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this -> window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &matrix);
    initializeCallbacks();
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    this->bezier.printBezierCurve(100, "../res/exp1.3.txt");
    this->bezier.printPoints();
    this->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
    this->SetVertices("../res/exp1.2.txt");
}
void Window::SetShader(const char *vertexPath, const char *fragmentPath)
{
    this -> shader = Shader(vertexPath, fragmentPath);
}
void Window::SetVertices(const char *dataPath)
{
    this -> vertices = Vertices(dataPath);
}
void Window::Show()
{
    shader.use();
    while (!glfwWindowShouldClose(window))
    {
        shader.setMat4("projection", matrix.projection);
        shader.setMat4("model", matrix.model);
        shader.setMat4("view", matrix.view);
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(cur_exp == E_Bezier)
        {
            this->SetVertices("../res/exp1.3.txt");
            vertices.DrawLine();
            for(int i=0;i<bezier.n;i++)
                bezier.DrawRedCircle(bezier.points[i].x, bezier.points[i].y, 0.005, 32);
            if(Istwo)
            {
                this->SetVertices("../res/exp1.4.txt");
                vertices.DrawLine();
            }    
        } 
        if(cur_exp == E_Cube)
            vertices.Draw();
        if(cur_exp == E_Model)
        {
            model.loadModel("../res/bunny/bunny_10k.obj");
            model.Draw();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    vertices.Clean();
    glfwTerminate();
}
void Window::initializeCallbacks()
{
    if(cur_exp == E_Cube || cur_exp == E_Model)
    {
        glfwSetKeyCallback(window, Matrix::KeyCallBack);
        glfwSetCursorPosCallback(window, Matrix::MouseCallBack);
    }
    if(cur_exp == E_Bezier)
    {
        glfwSetKeyCallback(window, Matrix::B_KeyCallBack);
        glfwSetCursorPosCallback(window, Matrix::B_MouseCallBack);
    }
}
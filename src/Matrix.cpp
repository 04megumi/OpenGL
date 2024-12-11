#include "Window.h"
#include "Matrix.h"

Matrix::Matrix(Window* w)
{
    this -> window = w;
    transModeSelected = Rotate;
    this -> model = glm::mat4(1.0f), this -> view = glm::mat4(1.0f), this -> projection = glm::mat4(1.0f);
    this -> transltation = glm::mat4(1.0f), this -> rotation = glm::mat4(1.0f), this -> scale = glm::mat4(1.0f);
    this -> cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
    this -> cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}
Matrix::Matrix()
{
}
void Matrix::handleKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::cout << "key" << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); 
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        model = glm::mat4(1.0f), view = glm::mat4(1.0f), projection = glm::mat4(1.0f);
        transltation = glm::mat4(1.0f), rotation = glm::mat4(1.0f), scale = glm::mat4(1.0f);
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        shouldDrawLine = !shouldDrawLine;
        if (shouldDrawLine)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        transModeSelected = Rotate;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        transModeSelected = Translate;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        transModeSelected = Scale;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        this->window->cur_exp = E_Bezier;
        this->window->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
        this->window->SetVertices("../res/exp1.3.txt");
        this->window->initializeCallbacks();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        this->window->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
        this->window->cur_exp = E_Model;
        this->window->initializeCallbacks();
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        this->window->cur_exp = E_Cube;
        this->window->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
        this->window->SetVertices("../res/exp1.2.txt");
        this->window->initializeCallbacks();
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        cameraPosition += cameraSpeed * cameraFront;
        cameraTarget += cameraSpeed *cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        cameraPosition -= cameraSpeed * cameraFront;
        cameraTarget -= cameraSpeed *cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPosition += cameraSpeed * cameraRight;
        cameraTarget += cameraSpeed *cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        cameraPosition -= cameraSpeed * cameraRight;
        cameraTarget -= cameraSpeed *cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cameraPosition += cameraSpeed * cameraUp;
        cameraTarget += cameraSpeed *cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        cameraPosition -= cameraSpeed * cameraUp;
        cameraTarget -= cameraSpeed *cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, 0.0f, 3.0f);     
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(-3.0f, 0.0f, 0.0f);  
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        cameraTarget = glm::vec3(3.0f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
        cameraTarget = glm::vec3(0.0f, -3.0f, 0.0f);  
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        cameraPosition = glm::vec3(0.0f, 3.0f, -2.99f);
        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
    model = transltation * rotation * scale;
    this -> window -> shader.setMat4("model", model);
    this -> window -> shader.setMat4("view", view);
}
void Matrix::handleMouseCallBack(GLFWwindow *window, double xpos, double ypos)
{
    //std::cout << "mouse xpos:" << xpos << " ypos: " << ypos << std::endl;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        if (lastX > this->window->width)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }
        float deltaX = xpos - lastX;
        float deltaY = ypos - lastY;
        if (transModeSelected == Translate)
            transltation = glm::translate(transltation, glm::vec3(deltaX / 100.0f, -deltaY / 100.0f, 0.0f));
        else if (transModeSelected == Rotate)
        {
            rotation = glm::rotate(rotation, glm::radians(deltaX / 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            rotation = glm::rotate(rotation, glm::radians(deltaY / 5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }
        else if (transModeSelected == Scale)
        {
            float scaleFactor = 1.0f + deltaY / 100.0f;
            scale = glm::scale(scale, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
        }
        model = transltation * rotation * scale;
        this->window->shader.setMat4("model", model);
        lastX = xpos;
        lastY = ypos;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        if (lastX > this->window->width)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // 注意 Y 轴是反的
        lastX = xpos;
        lastY = ypos;
        xoffset *= cameraSpeed;
        yoffset *= cameraSpeed;
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
        glm::mat4 rotationHorizontal = glm::rotate(glm::mat4(1.0f), glm::radians(-xoffset), cameraUp);
        glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));
        glm::mat4 rotationVertical = glm::rotate(glm::mat4(1.0f), glm::radians(-yoffset), right);
        glm::vec4 newFront = rotationHorizontal * rotationVertical * glm::vec4(cameraFront, 1.0f);
        cameraFront = glm::normalize(glm::vec3(newFront));
        cameraTarget = cameraPosition + cameraFront;
        view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        this->window->shader.setMat4("view", view);
    }
    else
    {
        lastX = 10000;
    }
}
void Matrix::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Matrix* instance = static_cast<Matrix*>(glfwGetWindowUserPointer(window));
    if (instance)
    {
        instance->handleKeyCallBack(window, key, scancode, action, mods);
    }
}
void Matrix::MouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
    Matrix* instance = static_cast<Matrix*>(glfwGetWindowUserPointer(window));
    if (instance)
    {
        instance->handleMouseCallBack(window, xpos, ypos);
    }
}
void Matrix::B_handleKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::cout << "key" << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); 
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        this->window->bezier = Bezier(10, 1);
        this->window->bezier.printBezierCurve(100, "../res/exp1.3.txt");
        this->window->bezier.printPoints();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        if(!this->window->Istwo)
        {
            Bezier bezier2 = Bezier(10, 2);
            bezier2.printBezierCurve(100, "../res/exp1.4.txt");
            std::cout << "第二条贝塞尔曲线生成成功" << std::endl;
            this->window->Istwo = true;
        }
        else
        {
            this->window->Istwo = false;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        transModeSelected = Translate;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        transModeSelected = Scale;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        this->window->cur_exp = E_Cube;
        this->window->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
        this->window->SetVertices("../res/exp1.2.txt");
        this->window->initializeCallbacks();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        this->window->SetShader("../shader/vectorShader.txt", "../shader/fragmentShader.txt");
        this->window->cur_exp = E_Model;
        this->window->initializeCallbacks();
    }
    view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
    model = transltation * rotation * scale;
    this -> window -> shader.setMat4("model", model);
    this -> window -> shader.setMat4("view", view);
    this -> window->SetVertices("../res/exp1.3.txt");
}
void Matrix::B_handleMouseCallBack(GLFWwindow *window, double xpos, double ypos)
{
    float x = float(xpos-0.5*this->window->width)/float(0.5*this->window->width), y = float(0.5*this->window->height-ypos)/float(0.5*this->window->height);
    //std::cout << "mouse xpos:" << xpos << " ypos: " << ypos << " (" << x << "," << y <<")" << std::endl;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        if (lastX > this->window->width)
        {
            lastX = xpos;
            lastY = ypos;
            return;
        }
        for(int i=0;i<this->window->bezier.n;i++)
        {
            float x0 = this->window->bezier.points[i].x;
            float y0 = this->window->bezier.points[i].y;
            if((x-x0<=0.15f)&&(x-x0>=0.0f) || (x0-x<=0.15f)&&(x0-x>=0.0f))
            {
                if((y-y0<=0.15f)&&(y-y0>=0.0f) || (y0-y<=0.15f)&&(y0-y>=0.0f))
                {
                    std::cout << " (" << x << "," << y << ")" ;
                    std::cout << i << ": (" << x0 << "," << y0 << ") is clicked" << std::endl;
                    this->window->bezier.points[i].x = x, this->window->bezier.points[i].y = y;
                    this->window->bezier.printBezierCurve(100, "../res/exp1.3.txt");
                }
            }
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        int cur = this->window->bezier.n;
        int now = this->window->bezier.now;
        this->window->bezier = Bezier(++cur, now);
    }
    else
    {
        lastX = 10000;
    }
    this -> window->SetVertices("../res/exp1.3.txt");
}
void Matrix::B_KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Matrix* instance = static_cast<Matrix*>(glfwGetWindowUserPointer(window));
    if (instance)
    {
        instance->B_handleKeyCallBack(window, key, scancode, action, mods);
    }
}
void Matrix::B_MouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
    Matrix* instance = static_cast<Matrix*>(glfwGetWindowUserPointer(window));
    if (instance)
    {
        instance->B_handleMouseCallBack(window, xpos, ypos);
    }
}
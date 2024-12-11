#ifndef MATRIX_H
#define MATRIX_H
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp> 
#include <GLFW/glfw3.h>

class Window;


enum TransMode
{
    Translate,
    Rotate,
    Scale
};

class Matrix 
{
public:
    Window* window = nullptr;
    TransMode transModeSelected;
    glm::mat4 model, view, projection;
    glm::mat4 transltation, rotation, scale;
    glm::vec3 cameraPosition, cameraTarget, cameraUp;
    float cameraSpeed = 0.05f;
    bool shouldDrawLine = false;
    float lastX = 10000, lastY = 10000;
public:
    Matrix(Window* w);
    Matrix();
    void handleKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleMouseCallBack(GLFWwindow* window, double xpos, double ypos);
    void B_handleKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    void B_handleMouseCallBack(GLFWwindow* window, double xpos, double ypos);
    static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseCallBack(GLFWwindow* window, double xpos, double ypos);
    static void B_KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void B_MouseCallBack(GLFWwindow* window, double xpos, double ypos);
};

#endif

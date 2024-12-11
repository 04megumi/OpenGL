#ifndef WINDOW_H
#define WINDOW_H 

#include "Vertices.h"
#include "Shader.h"
#include "Bezier.h"
#include "Matrix.h"
#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

enum Exp 
{
    E_Cube, E_Bezier, E_Model
};

class Window
{
public:
    GLFWwindow* window;      //window
    const int width, height; //窗口大小

    //四个主要组成部件
    Shader shader;           //着色器
    Vertices vertices;       //顶点
    Matrix matrix;           //矩阵运算
    Bezier bezier;          //贝塞尔曲线
    Model model;             //模型引入

    Exp cur_exp = E_Cube;    //当前实验状态
    bool Istwo = false;

public:
    Window(int w, int h, const char* title);                               //构造函数
    void SetShader(const char* vertexPath, const char* fragmentPath);      //设置着色器
    void SetVertices(const char *dataPath);                                //设置顶点数据
    void Show();                                                           //绘制
    void initializeCallbacks();                                            //设置回调函数
};

#endif
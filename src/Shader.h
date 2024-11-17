#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // 着色器程序ID
    unsigned int ID;

    // 构造函数, 读取并编译着色器
    Shader(const char* vertexPath, const char* fragmentPath);
    // 激活程序
    void use();
    // uniform工具函数 用于修改uniform变量的值
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
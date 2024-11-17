#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    //1. 读取着色器代码
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 确保ifstream可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        {
            // 打开着色器txt文件
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // 读取文件中的字符内容到stringstream中
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // 关闭txt文件
            vShaderFile.close();
            fShaderFile.close();
            // 转换stringstream为string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }

    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2.编译着色器代码
    unsigned int vertex, fragment;
    // 编译顶点着色器代码并检查错误
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX"); 
    // 编译片段着色器代码并错误检查
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(fragment, "FRAGMENT")
    // 创建程序， 将着色器连接到程序上并错误检查
    ID = glCreateProgram();
    glAttachShader(ID, vertex); //把着色器连接到程序上
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
   // 释放顶点和片段着色器
   glDeleteShader(vertex);
   glDeleteShader(vertex);
}

void Shader::use()
{
    glUserProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM");
    {
        glGetShaderiv(shader, GL_COMPILESTATUS, &success);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
            << infoLog << "\n -- --------------------" << std::endl;
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
            << infoLog << "\n -- --------------------" << std::endl;
        }
    }
}

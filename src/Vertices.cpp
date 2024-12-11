#include "Vertices.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
Vertices::Vertices(){}
Vertices::Vertices(const char *dataPath)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::ifstream file(dataPath);
    std::string line;
    bool isIndex = false; 
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (line[0] == '#') 
        {
            if (line.find("索引") != std::string::npos) 
                isIndex = true;
            continue;
        }
        if (isIndex)
        {
            unsigned int index;
            while (iss >> index)
                indices.push_back(index);
        }
        else
        {
            float vertex;
            while (iss >> vertex)
                vertices.push_back(vertex);
        }
    }
    file.close();
    num = indices.size();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}
void Vertices::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Vertices::DrawLine()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, num, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void Vertices::Clean()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
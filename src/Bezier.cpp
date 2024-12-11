#include "Bezier.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>


Bezier::Bezier(int num, int now) : n(num), now(now)
{
    generateRandomPoints();
}
void Bezier::generateRandomPoints() {
    if(now == 1)
    {
        float frequency = 2.0f * M_PI;  // 控制震荡的频率
        for (int i = 0; i < n; ++i) {
            point p;
            // 使用正弦函数生成震荡的 x 和 y 坐标，范围在 -1 到 1
            p.x = std::sin(frequency * (float)i / n);  // 震荡函数，x 从 -1 到 1
            p.y = std::cos(frequency * (float)i / n);  // 震荡函数，y 从 -1 到 1
            p.z = 0.0f;  // z 坐标保持为 0
            points.push_back(p);
        }
    }
    if(now == 2)
    {
        float a = 1.0f;  // 控制二次函数的系数
        float b = 0.0f;  // 一次项系数
        float c = 0.0f;  // 常数项

        for (int i = 0; i < n; ++i)
        {
            point p;
            float t = -1.0f + 2.0f * (float)i / (n - 1);  // 生成 [-1, 1] 范围内的 t 值
            p.x = t;                       // x 坐标为 t
            p.y = a * t * t + b * t + c;   // y 坐标通过二次函数生成
            p.z = 0.0f;                    // z 坐标保持为 0
            points.push_back(p);
        }
    }
}
void Bezier::printPoints()
{
    for (const auto &p : points)
    {
        std::cout << "Point: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
    }
}
point Bezier::calculateBezierPoint(float t)
{
    point result = {0.0f, 0.0f, 0.0f}; // 初始化为 0
    for (int i = 0; i < n; ++i)
    {
        float binomialCoeff = std::tgamma(n) / (std::tgamma(i + 1) * std::tgamma(n - i));
        float weight = binomialCoeff * std::pow(t, i) * std::pow(1 - t, n - i);
        result.x += weight * points[i].x;  
        result.y += weight * points[i].y; 
        result.z = 0.0f; // 始终设为 0
    }
    return result;
}
void Bezier::DrawRedCircle(float x, float y, float radius, int segments)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    const float PI = 3.14159265359f;
    vertices.push_back(x); // 圆心 x
    vertices.push_back(y); // 圆心 y
    vertices.push_back(0.0f); 
    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * PI * i / segments;
        float xc = x + radius * cos(angle); // x 坐标
        float yc = y + radius * sin(angle); // y 坐标
        vertices.push_back(xc);
        vertices.push_back(yc);
        vertices.push_back(0.0f);
    }
    for (int i = 1; i <= segments; ++i)
    {
        indices.push_back(0);    // 圆心索引
        indices.push_back(i);    // 当前顶点
        indices.push_back(i + 1);// 下一个顶点
    }
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Bezier::printBezierCurve(int num_points, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }
    file << "# 顶点数据 (位置 + 颜色)\n";
    for (int i = 0; i <= num_points; ++i)
    {
        float t = (float)i / num_points;  // 生成 t 从 0 到 1
        point p = calculateBezierPoint(t);
        float r = (std::rand() / (float)RAND_MAX);
        float g = (std::rand() / (float)RAND_MAX);
        float b = (std::rand() / (float)RAND_MAX);
        file << p.x << " " << p.y << " " << p.z << "  "
             << r << " " << g << " " << b << "\n";
    }
    file << "\n# 索引数据\n";
    for (int i = 0; i < num_points; ++i)
    {
        file << i << " " << (i + 1) << "\n";
    }
    file.close();
}
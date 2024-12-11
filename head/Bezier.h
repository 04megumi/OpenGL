#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <glad/glad.h>

// 控制点结构体
struct point
{
    float x, y, z;
};


class Bezier
{
public:
    int n;
    std::vector<point> points;
    int now = 1;
public:
    Bezier(int num, int now);
    void generateRandomPoints();
    void printPoints();
    point calculateBezierPoint(float t);
    void printBezierCurve(int num_points, const std::string &filename);
    void DrawRedCircle(float x, float y, float radius, int segments);
};

#endif

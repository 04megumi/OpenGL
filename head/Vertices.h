#ifndef VERTICES_H
#define VERTICES_H

class Vertices
{
public:
    unsigned int VAO, VBO, EBO;
    int num;
public:
    Vertices();
    Vertices(const char* dataPath);
    void Draw();
    void DrawLine();
    void Clean();
};

#endif 

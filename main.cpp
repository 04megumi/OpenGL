#include "Window.h"


int main()
{

    Window w(800, 600, "计算机图形学实验");
    glEnable(GL_DEPTH_TEST);
    w.Show();

    return 0;
}
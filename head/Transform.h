#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum TransMode
{
    Translate,
    Rotate,
    Scale
};



class Transform {
public:
    // 转换模式
    TransMode transModeSelected;
    // 矩阵变换时，需要用到的六个矩阵
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 transltation;
    glm::mat4 rotation;
    glm::mat4 scale;
    glm::mat4 groundModel;
    // 一些向量
    glm::vec3 cameraPosition; 
    glm::vec3 cameraTarget;
    glm::vec3 cameraUp; 
    
    bool shouldDrawLine = false;

    Transform();
    void Init();
    void W();
    void S();
    void D();
    void A();
    void Q();
    void E();
    void F2();
    void F3();
    void F4();
    void F5();
    void F6();
    void update();
};




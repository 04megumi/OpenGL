#include "Transform.h"

Transform::Transform()
{
    Init();
}

void Transform::Init()
{
    transModeSelected = Rotate;

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    transltation = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    groundModel = glm::mat4(1.0f);

    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    shouldDrawLine = false;
}

void Transform::W()
{
    glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
    cameraPosition += cameraSpeed * cameraFront;
    cameraTarget += cameraSpeed * cameraFront;
}

void Transform::S()
{
    glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
    cameraPosition -= cameraSpeed * cameraFront;
    cameraTarget -= cameraSpeed *cameraFront;
}

void Transform::D()
{
    glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    cameraPosition += cameraSpeed * cameraRight;
    cameraTarget += cameraSpeed *cameraRight;
}

void Transform::A()
{
    glm::vec3 cameraFront = glm::normalize(cameraTarget-cameraPosition);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
    cameraPosition -= cameraSpeed * cameraRight;
    cameraTarget -= cameraSpeed *cameraRight;
}

void Transform::Q()
{
    cameraPosition += cameraSpeed * cameraUp;
    cameraTarget += cameraSpeed *cameraUp;
}

void Transform::E()
{
    cameraPosition -= cameraSpeed * cameraUp;
    cameraTarget -= cameraSpeed *cameraUp;
}

void Transform::F2()
{
    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    cameraTarget = glm::vec3(0.0f, 0.0f, -3.0f);
}

void Transform::F3()
{
    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    cameraTarget = glm::vec3(0.0f, 0.0f, 3.0f);     
}

void Transform::F4()
{
    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    cameraTarget = glm::vec3(-3.0f, 0.0f, 0.0f);  
}

void Transform::F5()
{
    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraTarget = glm::vec3(3.0f, 0.0f, 0.0f);
}

void Transform::F6()
{
    cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
    cameraTarget = glm::vec3(0.0f, -3.0f, 0.0f); 
}

void Transform::update()
{
    model = transltation * rotation * scale;
    view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

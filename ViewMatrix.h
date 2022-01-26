#pragma once
#include "Matrix4.h"
#include "CameraPos.h"
#include "CameraFront.h"
#include "CameraUp.h"
/**
*/
class ViewMatrix :
    private Matrix4
{
public:
    /**
    * Interfaces
    */
    virtual glm::mat4 getMatrix() const override;
    void cameraTranslationSpeed(float speed);
    void cameraRotationSpeed(float speed);
    void addVec(const glm::vec3& addVec);
    void rotate(float addYaw, float addPitch);

    /**
    * Constructor
    */
    ViewMatrix(std::shared_ptr<CameraPos> _cameraPo, 
        std::shared_ptr<CameraFront> _cameraFront, 
        std::shared_ptr<CameraUp> _cameraUp);
    ViewMatrix();
    ~ViewMatrix();

private:
    /**
    * Members
    */
    std::shared_ptr<CameraPos> cameraPos;
    std::shared_ptr<CameraFront> cameraFront;
    std::shared_ptr<CameraUp> cameraUp;
};


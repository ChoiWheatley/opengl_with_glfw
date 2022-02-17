#pragma once
#include "Matrix4.h"
#include "CameraPos.h"
#include "CameraFront.h"
#include "CameraUp.h"
/**
*/
class ViewMatrix :
    public Matrix4
{
public:
    /**
    * Interfaces
    */
    virtual glm::mat4 getMatrix() const override;
    /**
    * Constructor
    */
    ViewMatrix(
        std::shared_ptr<UnitVector> _cameraPos, 
        std::shared_ptr<UnitVector> _cameraFront, 
        std::shared_ptr<UnitVector> _cameraUp);
    ViewMatrix();
    ~ViewMatrix();

private:
    /**
    * Members
    */
    std::shared_ptr<UnitVector> cameraPos;
    std::shared_ptr<UnitVector> cameraFront;
    std::shared_ptr<UnitVector> cameraUp;
};


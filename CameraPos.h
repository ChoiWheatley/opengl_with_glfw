#pragma once
#include "UnitVector.h"
/**
* 
*/
struct CameraPos :
    private UnitVector
{
public:
    /**
    * Interfaces
    */
    void translate(const glm::vec3& addVec);
    /**
    * Constructor
    */
    CameraPos(const glm::vec3& position, float speed);
    CameraPos();
    /**
    * Public Members
    */
    float speed;
protected:
    virtual glm::vec3 getVector() final;
    /**
    * Private Members
    */
    glm::vec3 position;
};


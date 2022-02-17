#pragma once
#include "UnitVector.h"

/**
* 
*/
struct CameraPos :
    public UnitVector
{
public:
    /**
    * Interfaces
    */
    virtual glm::vec3 getVector() override;
    void addVec(const glm::vec3& addVec);
    /**
    * Constructor
    */
    CameraPos(const glm::vec3& position, float speed);
    CameraPos();
    /**
    * Public Members
    */
    float speed;
private:
    glm::vec3 position;
};


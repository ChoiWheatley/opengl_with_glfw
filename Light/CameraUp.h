#pragma once
#include "UnitVector.h"

/**
* 얘는 단순히 벡터를 들고만 있어도 된다. 뭐 변경이 필요한 것도
* 아니고 요청에 따라 열심히 건네주기만 하면 된다.
*/
struct CameraUp :
    public UnitVector
{
public:
    CameraUp(glm::vec3 initUp);
    CameraUp();
    virtual glm::vec3 getVector() override;
private:
    glm::vec3 vec;
};


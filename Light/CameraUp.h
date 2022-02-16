#pragma once
#include "UnitVector.h"

/**
* ��� �ܼ��� ���͸� ��� �־ �ȴ�. �� ������ �ʿ��� �͵�
* �ƴϰ� ��û�� ���� ������ �ǳ��ֱ⸸ �ϸ� �ȴ�.
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


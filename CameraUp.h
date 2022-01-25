#pragma once
#include "UnitVector.h"
/**
* ��� �ܼ��� ���͸� ��� �־ �ȴ�. �� ������ �ʿ��� �͵�
* �ƴϰ� ��û�� ���� ������ �ǳ��ֱ⸸ �ϸ� �ȴ�.
*/
struct CameraUp :
    private UnitVector
{
public:
    CameraUp(glm::vec3 initUp);
    CameraUp();
private:
    virtual glm::vec3 getVector() override;
    glm::vec3 vec;
};


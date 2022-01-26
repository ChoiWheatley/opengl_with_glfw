#pragma once
#include "UnitVector.h"

/**
* vector 값을 직접 다루지 않는다. Yaw(좌우 혹은 y축)와 Pitch(상하 혹은 x축)
* 을 기반으로 카메라 객체가 필요로 하는 방향벡터를 계산한다. 물론 실제 position
* 에 기반한 벡터는 아니고 정규화된 방향벡터만을 취급한다는 점.
*/
struct CameraFront :
    public UnitVector
{
public:
    /**
    * Interfaces
    */
    /*yaw, pitch를 가지고 즉석에서 벡터를 계산한다.*/
    virtual glm::vec3 getVector() override;
    void addYaw(float degree);
    void addPitch(float degree);
    /**
    * Constructor
    */
    CameraFront(float speed, float yaw, float pitch);
    CameraFront();
    /**
    * Public Members
    */
    float speed;
private:
    /**
    * Members
    */
    float yaw;
    float pitch;
};


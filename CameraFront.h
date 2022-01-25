#pragma once
#include "UnitVector.h"
/**
* vector ���� ���� �ٷ��� �ʴ´�. Yaw(�¿� Ȥ�� y��)�� Pitch(���� Ȥ�� x��)
* �� ������� ī�޶� ��ü�� �ʿ�� �ϴ� ���⺤�͸� ����Ѵ�. ���� ���� position
* �� ����� ���ʹ� �ƴϰ� ����ȭ�� ���⺤�͸��� ����Ѵٴ� ��.
*/
struct CameraFront :
    private UnitVector
{
public:
    /**
    * Interfaces
    */
    void addYaw(float degree);
    void addPitch(float degree);
    /**
    * Constructor
    */
    CameraFront(float speed, 
        float yaw, 
        float pitch);
    CameraFront();
    /**
    * Public Members
    */
    float speed;
protected:
    /*yaw, pitch�� ������ �Ｎ���� ���͸� ����Ѵ�.*/
    virtual glm::vec3 getVector() final;
private:
    /**
    * Members
    */
    float yaw;
    float pitch;
};


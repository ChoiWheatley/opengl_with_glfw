#pragma once
#include "UnitVector.h"

/**
* vector ���� ���� �ٷ��� �ʴ´�. Yaw(�¿� Ȥ�� y��)�� Pitch(���� Ȥ�� x��)
* �� ������� ī�޶� ��ü�� �ʿ�� �ϴ� ���⺤�͸� ����Ѵ�. ���� ���� position
* �� ����� ���ʹ� �ƴϰ� ����ȭ�� ���⺤�͸��� ����Ѵٴ� ��.
*/
struct CameraFront :
    public UnitVector
{
public:
    /**
    * Interfaces
    */
    /*yaw, pitch�� ������ �Ｎ���� ���͸� ����Ѵ�.*/
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


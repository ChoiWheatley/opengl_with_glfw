#include "CameraFront.h"

glm::vec3 CameraFront::getVector()
{
    //TODO: yaw랑 pitch로 벡터 생성하여 리턴하기
}

void CameraFront::addYaw(float degree)
{
    yaw += degree;
}

void CameraFront::addPitch(float degree)
{
    pitch += degree;
}

CameraFront::CameraFront(float speed, float yaw, float pitch)
	:speed{ speed }, yaw{ yaw }, pitch{ pitch }
{}

CameraFront::CameraFront()
{
    speed = Constants::Camera::rotationSpeed;
    yaw = Constants::Camera::initYaw;
    pitch = Constants::Camera::initPitch;
}

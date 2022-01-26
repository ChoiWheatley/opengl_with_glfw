#include "CameraFront.h"

glm::vec3 CameraFront::getVector()
{
    if (pitch > 89.f)
        pitch = 89.f;
    if (pitch < -89.f)
        pitch = 89.f;

    auto ryaw = glm::radians(yaw);
    auto rpitch = glm::radians(pitch);

    return glm::normalize(
        glm::vec3{
            cos(ryaw) * cos(rpitch),
            sin(rpitch),
            sin(ryaw) * cos(rpitch)
        }
    );
}

void CameraFront::addYaw(float degree)
{
    yaw += degree * speed;
}

void CameraFront::addPitch(float degree)
{
    pitch += degree * speed;
}

CameraFront::CameraFront(float speed, float yaw, float pitch)
	: UnitVector(), speed{ speed }, yaw{ yaw }, pitch{ pitch }
{}

CameraFront::CameraFront()
	: UnitVector()
{
    speed = Constants::Camera::rotationSpeed;
    yaw = Constants::Camera::initYaw;
    pitch = Constants::Camera::initPitch;
}

#include "CameraPos.h"

void CameraPos::translate(const glm::vec3& addVec)
{
	position += addVec;
}

CameraPos::CameraPos(const glm::vec3& position, float speed)
	:position{ position }, speed{ speed }
{
}

CameraPos::CameraPos()
{
	speed = Constants::Camera::translationSpeed;
	position = Constants::Camera::initPosition;
}

glm::vec3 CameraPos::getVector()
{
	return position;
}

#include "CameraPos.h"

void CameraPos::addVec(const glm::vec3& addVec)
{
	position += addVec;
}

CameraPos::CameraPos(const glm::vec3& position, float speed)
	:UnitVector(), position{ position }, speed{ speed }
{}

CameraPos::CameraPos()
	:UnitVector()
{
	
	speed = Constants::Camera::translationSpeed;
	position = Constants::Camera::initPosition;
}

glm::vec3 CameraPos::getVector()
{
	return position;
}

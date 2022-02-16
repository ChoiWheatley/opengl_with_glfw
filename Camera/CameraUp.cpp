#include "CameraUp.h"

CameraUp::CameraUp(glm::vec3 initUp)
	: UnitVector(), vec{ initUp }{}

CameraUp::CameraUp()
	: UnitVector()
{
	vec = Constants::Camera::initUp;
}

glm::vec3 CameraUp::getVector()
{
	return vec;
}

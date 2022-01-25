#include "CameraUp.h"

CameraUp::CameraUp(glm::vec3 initUp)
	:vec{ initUp }{}

CameraUp::CameraUp()
{
	vec = Constants::Camera::initUp;
}

glm::vec3 CameraUp::getVector()
{
	return vec;
}

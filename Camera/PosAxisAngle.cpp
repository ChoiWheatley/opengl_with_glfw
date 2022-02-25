#include "PosAxisAngle.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 PosAxisAngle::getMatrix() const
{
	glm::mat4 ret{1.f};
	ret = glm::translate(ret, pos);
	ret = glm::rotate(ret, angle, axis);
	return ret;
}

void PosAxisAngle::translate(const glm::vec3& vec)
{
	pos += vec;
}

void PosAxisAngle::rotate(const float& deltaAngle)
{
	angle += deltaAngle;
}

void PosAxisAngle::operator+(const PosAxisAngle& paa)
{
	pos += paa.pos;
	axis += paa.axis;
	angle += paa.angle;
}

PosAxisAngle::PosAxisAngle(glm::vec3 pos, glm::vec3 axis, const float angle)
	:pos{ pos }, axis{ axis }, angle{ angle }
{}

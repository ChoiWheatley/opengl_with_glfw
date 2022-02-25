#pragma once
#include <memory>
#include "PosAxisAngle.h"
struct PosAxisAngleFactory : public Matrix4
{
	static std::unique_ptr<PosAxisAngle> make(const glm::vec3& pos, const glm::vec3& axis, const float& angle)
	{
		return std::make_unique<PosAxisAngle>(pos, axis, angle);
	}
};

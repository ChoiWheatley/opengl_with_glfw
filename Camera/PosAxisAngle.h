#pragma once
#include "Matrix4.h"

struct PosAxisAngle final : public Matrix4
{
public: // interface
	glm::mat4 getMatrix() const override;
	void translate(const glm::vec3& vec);
	void rotate(const float& deltaAngle);
	void operator+(const PosAxisAngle& paa);
public: // constructor
	PosAxisAngle(glm::vec3 pos, glm::vec3 axis, const float angle);
	~PosAxisAngle() override = default;
public: // member
	glm::vec3 pos;
	glm::vec3 axis;
	float angle;
};

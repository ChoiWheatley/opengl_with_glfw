#include "ViewMatrix.h"

glm::mat4 ViewMatrix::getMatrix() const
{
	/*굳이 이렇게 해야하나 싶지만 그냥 나는 getVector()를
	숨기고 싶었다. glm의 `not method, do function` 에서 
	영감을 얻음.*/
	return glm::lookAt(
		getVector((UnitVector*)&cameraPos),
		getVector((UnitVector*)&cameraFront),
		getVector((UnitVector*)&cameraUp)
	);
}

void ViewMatrix::cameraTranslationSpeed(float speed)
{
	cameraPos->speed = speed;
}

void ViewMatrix::cameraRotationSpeed(float speed)
{
	cameraFront->speed = speed;
}

void ViewMatrix::translate(const glm::vec3& addVec)
{
	cameraPos->translate(addVec);
}

void ViewMatrix::rotate(float addYaw, float addPitch)
{
	cameraFront->addPitch(addPitch);
	cameraFront->addYaw(addYaw);
}

ViewMatrix::ViewMatrix(std::shared_ptr<CameraPos> _cameraPo, std::shared_ptr<CameraFront> _cameraFront, std::shared_ptr<CameraUp> _cameraUp)
	: cameraPos{ _cameraPo }, cameraFront{ _cameraFront }, cameraUp{ cameraUp }
{}

ViewMatrix::ViewMatrix()
	: cameraPos{ std::make_shared<CameraPos>() },
	cameraFront{ std::make_shared<CameraFront>() },
	cameraUp{ std::make_shared<CameraUp>() }
{}

ViewMatrix::~ViewMatrix()
{
	cameraPos.reset();
	cameraFront.reset();
	cameraUp.reset();
}

glm::vec3 ViewMatrix::getVector(UnitVector* vec) const
{
	return vec->getVector();
}


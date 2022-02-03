#include "ViewMatrix.h"

glm::mat4 ViewMatrix::getMatrix() const
{
	auto pos = cameraPos->getVector();
	auto front = cameraFront->getVector();
	auto up = cameraUp->getVector();

	return glm::lookAt(pos, pos + front, up);
}

ViewMatrix::ViewMatrix(std::shared_ptr<UnitVector> _cameraPo, std::shared_ptr<UnitVector> _cameraFront, std::shared_ptr<UnitVector> _cameraUp)
	: cameraPos{ _cameraPo }, cameraFront{ _cameraFront }, cameraUp{ _cameraUp }
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

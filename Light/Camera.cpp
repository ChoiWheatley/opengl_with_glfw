#include "Camera.h"

glm::mat4 Camera::getViewMatrix() const
{
	return this->viewMatrix->getMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return this->projectionMatrix->getMatrix();
}

Camera::Camera(std::shared_ptr<Matrix4> _projectionMatrix, std::shared_ptr<Matrix4> _viewMatrix)
{
	projectionMatrix = _projectionMatrix;
	viewMatrix = _viewMatrix;
}

Camera::Camera(std::shared_ptr<Matrix4> _projectionMatrix, std::shared_ptr<UnitVector> _pos, std::shared_ptr<UnitVector> _front, std::shared_ptr<UnitVector> _up)
{
	projectionMatrix = _projectionMatrix;
	viewMatrix = std::make_shared<ViewMatrix>(_pos, _front, _up);
}

Camera::Camera()
{
	projectionMatrix =std::make_shared<Projection>();
	viewMatrix = std::make_shared<ViewMatrix>();
}

Camera::~Camera()
{
	projectionMatrix.reset();
	viewMatrix.reset();
}


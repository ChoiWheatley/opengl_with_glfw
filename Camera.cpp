#include "Camera.h"

glm::mat4 Camera::getViewMatrix() const
{
	return this->viewMatrix->getMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return this->projectionMatrix->getMatrix();
}

void Camera::cameraTranslationSpeed(float speed)
{
	viewMatrix->cameraTranslationSpeed(speed);
}

void Camera::cameraRotationSpeed(float speed)
{
	viewMatrix->cameraRotationSpeed(speed);
}

void Camera::translateCamera(const glm::vec3& addVec)
{
	viewMatrix->addVec(addVec);
}

void Camera::rotateCamera(float addYaw, float addPitch)
{
	viewMatrix->rotate(addYaw, addPitch);
}

void Camera::addFOV(float add) 
{
	this->projectionMatrix->addFOV(add);
}

void Camera::setAspectRatio(float ratio)
{
	projectionMatrix->aspectRatio = ratio;
}

void Camera::setNear(float near)
{
	projectionMatrix->near = near;
}

void Camera::setFar(float far)
{
	projectionMatrix->far = far;
}

Camera::Camera(std::shared_ptr<Projection> _projectionMatrix, std::shared_ptr<ViewMatrix> _viewMatrix)
{
	projectionMatrix = _projectionMatrix;
	viewMatrix = _viewMatrix;
}

Camera::Camera()
{
	projectionMatrix = std::make_shared<Projection>();
	viewMatrix = std::make_shared<ViewMatrix>();
}

Camera::~Camera()
{
	projectionMatrix.reset();
	viewMatrix.reset();
}


#include "ViewMatrix.h"

glm::mat4 ViewMatrix::getMatrix() const
{
	/*���� �̷��� �ؾ��ϳ� ������ �׳� ���� getVector()��
	����� �;���. glm�� `not method, do function` ���� 
	������ ����.*/
	return glm::lookAt(
		cameraPos->getVector(),
		cameraFront->getVector(),
		cameraUp->getVector()
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

void ViewMatrix::addVec(const glm::vec3& addVec)
{
	cameraPos->addVec(addVec);
}

void ViewMatrix::rotate(float addYaw, float addPitch)
{
	cameraFront->addPitch(addPitch);
	cameraFront->addYaw(addYaw);
}

ViewMatrix::ViewMatrix(std::shared_ptr<CameraPos> _cameraPo, std::shared_ptr<CameraFront> _cameraFront, std::shared_ptr<CameraUp> _cameraUp)
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

#pragma once
#include "ViewMatrix.h"
#include "Projection.h"

/**
* Ŭ���̾�Ʈ�� �����ϴ� ī�޶� ��ü. projection matrix�� ���� ViewFrustum�� ������ �� �ִ�.
* view matrix�� ���� ViewMatrix�� ������ �� �ִ�. ī�޶� �⺻ �Ӽ��鿡 ���� �������� ������
* ����Ѵ�. 
*/
class Camera
{
public:
	/**
	* Interfaces
	*/
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	/*CameraPos���� ����ϴ� Translation�� ��ü���� �ӵ��� ������ �� �ִ�.*/
	void cameraTranslationSpeed(float speed);
	/*CameraFront���� ����ϴ� Rotation�� ���콺 �ΰ����� ������ �� �ִ�.*/
	void cameraRotationSpeed(float speed);
	/*�ܼ��� ���� position ���Ϳ� addVec�� ���Ѵ�.*/
	void translateCamera(const glm::vec3& addVec);
	/*yaw(�¿� Ȥ�� y�� ȸ��), pitch(���� Ȥ�� x�� ȸ��) ���� ���Ѵ�. degree��.*/
	void rotateCamera(float addYaw, float addPitch);
	/*field of view ���� �����Ѵ�.*/
	void addFOV(float add);
	void setAspectRatio(float ratio);
	void setNear(float near);
	void setFar(float far);
	/**
	* Constructor and Destructor
	*/
	Camera(std::shared_ptr<Projection> _projectionMatrix, std::shared_ptr<ViewMatrix> _viewMatrix);
	Camera();
	~Camera();

private:
	/**
	* Members
	*/
	/*view frustum�� �ʿ��� aspect ratio, near, far, fov � ���� �����͸� ĸ��ȭ��.*/
	std::shared_ptr<Projection> projectionMatrix;
	/*view matrix�� ����� �� ���Ǵ� `lookat()` �Լ��� �� ���ڸ� �߽����� ���¿� �ൿ�� 
	�߻�ȭ�Ѵ�. position, target, up */
	std::shared_ptr<ViewMatrix> viewMatrix;
};


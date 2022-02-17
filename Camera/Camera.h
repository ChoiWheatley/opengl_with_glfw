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
	/**
	* Constructor and Destructor
	*/
	explicit Camera(std::shared_ptr<Matrix4> _projectionMatrix, 
		std::shared_ptr<Matrix4> _viewMatrix);
	explicit Camera(std::shared_ptr<Matrix4> _projectionMatrix,
		std::shared_ptr<UnitVector> _pos,
		std::shared_ptr<UnitVector> _front,
		std::shared_ptr<UnitVector> _up
	);
	explicit Camera();
	~Camera();

private:
	/**
	* Members
	*/
	/*view frustum�� �ʿ��� aspect ratio, near, far, fov � ���� �����͸� ĸ��ȭ��.*/
	std::shared_ptr<Matrix4> projectionMatrix;
	/*view matrix�� ����� �� ���Ǵ� `lookat()` �Լ��� �� ���ڸ� �߽����� ���¿� �ൿ�� 
	�߻�ȭ�Ѵ�. position, target, up */
	std::shared_ptr<Matrix4> viewMatrix;
};


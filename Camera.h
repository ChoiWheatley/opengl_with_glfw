#pragma once
#include "ViewMatrix.h"
#include "Projection.h"

/**
* 클라이언트와 협업하는 카메라 객체. projection matrix를 위한 ViewFrustum에 접근할 수 있다.
* view matrix를 위한 ViewMatrix에 접근할 수 있다. 카메라 기본 속성들에 대한 간접적인 접근을
* 허용한다. 
*/
class Camera
{
public:
	/**
	* Interfaces
	*/
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	/*CameraPos에서 담당하는 Translation의 전체적인 속도를 변경할 수 있다.*/
	void cameraTranslationSpeed(float speed);
	/*CameraFront에서 담당하는 Rotation의 마우스 민감도를 변경할 수 있다.*/
	void cameraRotationSpeed(float speed);
	/*단순히 기존 position 벡터에 addVec을 더한다.*/
	void translateCamera(const glm::vec3& addVec);
	/*yaw(좌우 혹은 y축 회전), pitch(상하 혹은 x축 회전) 값을 더한다. degree임.*/
	void rotateCamera(float addYaw, float addPitch);
	/*field of view 값을 조절한다.*/
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
	/*view frustum에 필요한 aspect ratio, near, far, fov 등에 대한 데이터를 캡슐화함.*/
	std::shared_ptr<Projection> projectionMatrix;
	/*view matrix를 만드는 데 사용되는 `lookat()` 함수의 세 인자를 중심으로 상태와 행동을 
	추상화한다. position, target, up */
	std::shared_ptr<ViewMatrix> viewMatrix;
};


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
	/*view frustum에 필요한 aspect ratio, near, far, fov 등에 대한 데이터를 캡슐화함.*/
	std::shared_ptr<Matrix4> projectionMatrix;
	/*view matrix를 만드는 데 사용되는 `lookat()` 함수의 세 인자를 중심으로 상태와 행동을 
	추상화한다. position, target, up */
	std::shared_ptr<Matrix4> viewMatrix;
};


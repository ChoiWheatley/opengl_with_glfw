#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Constants.h"
/*
* Superclass for `ViewFrustum` and `ViewMatrix`
* 원래는 Projection과 ViewMatrix 모두를 이 타입으로 
* 레퍼런스를 제공할 생각이었으나, 하위 타입에 메서드를 호출할
* 수 없다는 것을 깨달았다. 이 클래스는 단순히 반복되는 코드작업을
* 줄이기 위해 사용한다.
*/
class Matrix4
{
public:
	/**
	* Interfaces
	*/
	virtual glm::mat4 getMatrix() const = 0;
};


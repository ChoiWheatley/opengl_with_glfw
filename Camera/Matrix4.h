#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Constants.h"
/*
* Superclass for `ViewFrustum` and `ViewMatrix`
* ������ Projection�� ViewMatrix ��θ� �� Ÿ������ 
* ���۷����� ������ �����̾�����, ���� Ÿ�Կ� �޼��带 ȣ����
* �� ���ٴ� ���� ���޾Ҵ�. �� Ŭ������ �ܼ��� �ݺ��Ǵ� �ڵ��۾���
* ���̱� ���� ����Ѵ�.
*/
class Matrix4
{
public:
	/**
	* Interfaces
	*/
	virtual glm::mat4 getMatrix() const = 0;
};


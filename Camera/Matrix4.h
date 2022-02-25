#pragma once
#include <glm/gtc/type_ptr.hpp>
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

	virtual ~Matrix4() = default;
};


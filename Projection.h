#pragma once
#include "Matrix4.h"
/**
* View Frustum�� �ʿ��� �����͵��� ĸ��ȭ�Ѵ�.
* QUESTION: ��ǻ� �ڷ����� ���� �׳� struct�� 
* �����ع����� ����������� publicȭ �ع�����?
*/
struct Projection
	: public Matrix4
{
public:
	/**
	* Interfaces
	*/
	virtual glm::mat4 getMatrix() const override;
	void addFOV(float offset);
	/**
	* Constructor
	*/
	Projection(float aspectRatio, float near, float far, float fov, float fovMin, float fovMax);
	Projection();
	/**
	* public Members
	*/
	float aspectRatio;
	float near;
	float far;
private:
	/**
	* private mambers
	*/
	float fov;
	float fovMin;
	float fovMax;
};


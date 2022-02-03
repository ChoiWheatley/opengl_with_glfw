#pragma once
#include "Matrix4.h"
/**
* View Frustum에 필요한 데이터들을 캡슐화한다.
* QUESTION: 사실상 자료형에 가까운데 그냥 struct로 
* 선언해버리고 멤버변수들을 public화 해버릴까?
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


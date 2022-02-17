#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Node
{
public:
	virtual glm::mat4 getCoordSpace() = 0;
};

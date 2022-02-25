#pragma once
#include <glm/glm.hpp>

class Node
{
public:
	virtual glm::mat4 getCoordSpace() = 0;

	virtual ~Node() = default;
};

#pragma once
#include <memory>
#include "Node.h"
#include "ShaderI.h"
#include "VertexI.h"
#include "TextureI.h"

class Mesh : public Node
{
public: // interfaces
	virtual glm::mat4 getCoordSpace() override;


public: // constructor
	Mesh(
		std::unique_ptr<ShaderI> shader,
		std::unique_ptr<TextureI> texture,
		std::unique_ptr<VertexI> vertex
	);
	~Mesh();

private: // member
	std::unique_ptr<ShaderI> shader_;
	std::unique_ptr<TextureI> texture_;
	std::unique_ptr<VertexI> vertex_;
	glm::vec3 pos_;
	glm::vec3 axis_;
	float angle_;

private: // method
	static glm::mat4 getMatrix(const glm::vec3& pos, const glm::vec3& axis, const float angle);

};




#pragma once
#include <memory>
#include "Node.h"
#include "ShaderI.h"
#include "VertexI.h"
#include "TextureI.h"
#include "Matrix4.h"

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
	std::unique_ptr<Matrix4> matrix_;

private: // method
	static glm::mat4 getMatrix(const Matrix4& matrix);

};




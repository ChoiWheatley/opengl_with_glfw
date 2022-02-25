#pragma once
#include <memory>
#include "Mesh.h"
struct MeshFactory : public Node
{
	static std::unique_ptr<Mesh> makeMesh(std::unique_ptr<ShaderI> shader,
		std::unique_ptr<TextureI> texture,
		std::unique_ptr<VertexI> vertex
	)
	{
		return std::make_unique<Mesh>(std::move(shader),
			std::move(texture),
			std::move(vertex));
	}
};


#pragma once
#include "Mesh.h"

/**
 * \brief drawing implementation needs user's help!
 */
class MeshPainter final : public Mesh
{
public:
	MeshPainter(
		std::unique_ptr<ShaderI>& shader, 
		std::unique_ptr<TextureI>& texture,
		std::unique_ptr<VertexI>& vertex)
		: Mesh(std::move(shader), std::move(texture), std::move(vertex))
	{}

	void draw() const override
	{
		// TODO: implement `draw()`
	}
};
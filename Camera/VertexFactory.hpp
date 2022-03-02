#pragma once
#include <memory>
#include "Vertex.h"

struct VertexFactory
{
	static std::unique_ptr<Vertex> make(GLsizeiptr dataSize, const void * data, const std::vector<VertexAttribute_DS>& vertex_attribute)
	{
		return std::make_unique<Vertex>(dataSize, data, vertex_attribute);
	}
};

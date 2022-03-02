#pragma once
#include <memory>
#include "Vertex.h"
#include "VertexFactory.hpp"
#include "mock_vertex_data.h"

namespace VertexTest
{
	inline std::unique_ptr<Vertex> testVertexInit()
	{
		return VertexFactory::make(sizeof(MockVertexData::vertices), MockVertexData::vertices,
		                           MockVertexData::vertex_attribute);
	}

	inline void testVertexBinding(VertexI * v_i)
	{
		v_i->bindVao();
	}
}

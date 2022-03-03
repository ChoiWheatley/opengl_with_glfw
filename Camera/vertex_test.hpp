#pragma once
#include <memory>
#include "Vertex.h"
#include "VertexFactory.hpp"
#include "mock_vertex_data.h"
#include "Stub.h"

namespace VertexTest
{
	inline std::unique_ptr<Vertex> testVertexInit()
	{
		PRINT_FUNC;
		auto ret = VertexFactory::make(sizeof(MockVertexData::vertices), MockVertexData::vertices,
		                           MockVertexData::vertex_attribute);
		PRINT_SUCCESS;
		return ret;
	}

	inline void testVertexBinding(VertexI * v_i)
	{
		PRINT_FUNC;
		v_i->bindVao();
		PRINT_SUCCESS;
	}
}

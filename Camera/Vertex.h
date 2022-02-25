#pragma once
#include "VertexI.h"

class Vertex
	: VertexI
{
public: // interface
	void setVertexAttribute(GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
		const void* pointer) override;
public: // constructor and destructor
	~Vertex() override = default;
};


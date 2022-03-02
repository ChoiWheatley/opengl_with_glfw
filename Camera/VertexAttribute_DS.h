#pragma once
#include <glad/glad.h>
struct VertexAttribute_DS
{
	const GLuint index;
	const GLint size;
	const GLenum type;
	const GLboolean normalized;
	const GLsizei stride;
	const void * pointer;
};

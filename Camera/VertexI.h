#pragma once
#include <glad/glad.h>
/**
 * \brief raw vertex, tex_coord 데이터를 vbo에 담아 vao에 리턴하기,
 * vertex shader layout 번호와 vbo를 알맞게 가리키게 만들기
 */
class VertexI
{
public: // interfaces
	virtual void setVertexAttribute(GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) = 0;

};

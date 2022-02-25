#pragma once
#include <glad/glad.h>
/**
 * \brief raw vertex, tex_coord �����͸� vbo�� ��� vao�� �����ϱ�,
 * vertex shader layout ��ȣ�� vbo�� �˸°� ����Ű�� �����
 */
class VertexI
{
public: // interfaces
	virtual void setVertexAttribute(GLint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) = 0;

};

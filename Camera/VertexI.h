#pragma once
#include <glad/glad.h>
/**
 * \brief raw vertex, tex_coord �����͸� vbo�� ��� vao�� �����ϱ�,
 * vertex shader layout ��ȣ�� vbo�� �˸°� ����Ű�� �����
 */
class VertexI
{
public:
	virtual void bindVao() = 0;
};

#include "Vertex.h"

void Vertex::bindVao()
{
	glBindVertexArray(vao_);
}

Vertex::Vertex(const void* data, std::vector<VertexAttribute_DS> vertex_attributes)
	: vao_(gen_vao()), vbo_(gen_vbo()), data_(data), vertex_attributes_(std::move(vertex_attributes))
{
	glBindVertexArray(vao_);
	glBindBuffer(buffer_target, vbo_);

	assign_buffer_data(buffer_target, sizeof(data_), data_, buffer_usage);
	for(const auto v : vertex_attributes_)
	{
		vertexAttribPointer(v);
		glEnableVertexAttribArray(v.index);
	}

	glBindBuffer(buffer_target, 0);
	glBindVertexArray(vao_);
}

unsigned Vertex::gen_vao()
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	return vao;
}

unsigned Vertex::gen_vbo()
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	return vbo;
}

void Vertex::vertexAttribPointer(const VertexAttribute_DS& attr)
{
	glVertexAttribPointer(
		attr.index,
		attr.size,
		attr.type,
		attr.normalized,
		attr.stride,
		attr.pointer
	);
}

void Vertex::assign_buffer_data(GLenum target, const GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}

// TODO: implement Vertex
Vertex::~Vertex()
{
	// TODO: void * data 처리를 어떻게 해야 하지?
}

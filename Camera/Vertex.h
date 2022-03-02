#pragma once
#include <vector>
#include "VertexI.h"
#include "VertexAttribute_DS.h"

/**
 * \brief Vertex encapsulates VAO and VBO
 */
class Vertex final
	: public VertexI
{
public: // interface
	void bindVao() override;
public: // constructor and destructor
	Vertex(GLsizeiptr dataSize, const void * data, std::vector<VertexAttribute_DS> vertex_attributes);
	Vertex() = delete;
	~Vertex();

private: // method
	static unsigned int gen_vao();
	static unsigned int gen_vbo();
	static void vertexAttribPointer(const VertexAttribute_DS& attr);
	static void assign_buffer_data(GLenum target, const GLsizeiptr size, const void * data, GLenum usage);
private: // member
	const unsigned int vao_;
	const unsigned int vbo_;
	const GLsizeiptr dataSize_;
	const void * data_ = nullptr;
	const std::vector<VertexAttribute_DS> vertex_attributes_;
public: // public member
	GLenum buffer_usage = GL_STATIC_DRAW;
	GLenum buffer_target = GL_ARRAY_BUFFER;
};


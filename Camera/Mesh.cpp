#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

glm::mat4 Mesh::getCoordSpace()
{
    return getMatrix(*matrix_);
}

Mesh::Mesh(std::unique_ptr<ShaderI> shader, std::unique_ptr<TextureI> texture, std::unique_ptr<VertexI> vertex)
	: shader_{std::move(shader)}, texture_{std::move(texture)}, vertex_{std::move(vertex)}
{}

Mesh::~Mesh()
{
	shader_.reset();
	texture_.reset();
	vertex_.reset();
	matrix_.reset();
}

glm::mat4 Mesh::getMatrix(const Matrix4& matrix)
{
	return matrix.getMatrix();
}


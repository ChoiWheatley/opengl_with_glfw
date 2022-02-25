#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Mesh::getCoordSpace()
{
    return glm::mat4();
}

Mesh::Mesh(std::unique_ptr<ShaderI> shader, std::unique_ptr<TextureI> texture, std::unique_ptr<VertexI> vertex)
	: shader_{std::move(shader)}, texture_{std::move(texture)}, vertex_{std::move(vertex)}
{}

Mesh::~Mesh()
{
	shader_.reset();
	texture_.reset();
	vertex_.reset();
}

glm::mat4 Mesh::getMatrix(const glm::vec3& pos, const glm::vec3& axis, const float angle)
{
	glm::mat4 ret(1.f);
	ret = glm::translate(ret, pos);
	ret = glm::rotate(ret, angle, axis);
	return ret;
}

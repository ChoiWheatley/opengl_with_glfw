#pragma once
#include <memory>
#include <string>
#include "Node.h"

class ShaderI;
class TextureI;
class VertexI;

class Mesh : public Node
{
public: // interfaces
	virtual glm::mat4 getCoordSpace() override;
	int getVao();

public: // constructor
	Mesh(std::shared_ptr<ShaderI> shader,
		std::shared_ptr<TextureI> texture,
		std::shared_ptr<VertexI> vertex);

private: // member
	std::shared_ptr<ShaderI> shader;
	std::shared_ptr<TextureI> texture;
	std::shared_ptr<VertexI> vertex;
};

// shader�� �����ϴ� ��ü�� ������ �����ϴ� �������̽�.
class ShaderI
{
public: // interfaces
	virtual void setUniformValue(std::string name, const glm::mat4& value) const = 0;
	virtual void setUniformValue(std::string name, const glm::vec3& value) const = 0;
	virtual void setUniformValue(std::string name, float value) const = 0;
	virtual void setUniformValue(std::string name, int value) const = 0;
	virtual void setUniformValue(std::string name, bool value) const = 0;
	virtual void useShaderProgram() const = 0;
};

class TextureI
{
public: // interfaces

};

/**
 * \brief raw vertex, tex_coord �����͸� vbo�� ��� vao�� �����ϱ�,
 * vertex shader layout ��ȣ�� vbo�� �˸°� ����Ű�� �����
 */
class VertexI
{
public: // interfaces

};

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

// shader를 관리하는 객체의 역할을 정의하는 인터페이스.
class ShaderI
{
public: // interfaces
	virtual void setUniformValue(std::string name, const glm::mat4& value) = 0;
	virtual void setUniformValue(std::string name, const glm::vec3& value) = 0;
	virtual void setUniformValue(std::string name, float value) = 0;
	virtual void setUniformValue(std::string name, int value) = 0;
	virtual void useShaderProgram() = 0;
};

class TextureI
{
public: // interfaces

};

class VertexI
{
public: // interfaces

};

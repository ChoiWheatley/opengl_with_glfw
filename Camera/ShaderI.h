#pragma once
#include <string>
#include <glm/glm.hpp>
// shader�� �����ϴ� ��ü�� ������ �����ϴ� �������̽�.
class ShaderI
{
public:// interfaces
	/**
	 * \brief Shader code --> Shader program
	 */
	virtual void useShaderProgram() const = 0;
	/**
	 * \brief change uniform value
	 * \param name string literal pointing GLSL's uniform variable
	 * \param value value
	 */
	virtual void setUniformValue(const std::string& name, const glm::mat4& value) const = 0;
	virtual void setUniformValue(const std::string& name, const glm::vec3& value) const = 0;
	virtual void setUniformValue(const std::string& name, const glm::vec2& value) const = 0;
	virtual void setUniformValue(const std::string& name, float value) const = 0;
	virtual void setUniformValue(const std::string& name, int value) const = 0;
	virtual void setUniformValue(const std::string& name, bool value) const = 0;

	virtual ~ShaderI() = default;
};

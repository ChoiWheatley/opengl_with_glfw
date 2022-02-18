#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Mesh.h"

/**
 * \brief impl version of ShaderI
 * Shader의 역할
 * - 셰이더 코드를 컴파일, 링크하여 Shader Program id를 보관한다.
 * - 셰이더 코드에서 사용하는 모든 uniform variable, layout location 변수들을 관리한다.
 * ------> 별도의 세부사항을 담은 객체로 책임을 위임하자.
 */
class Shader :
    public ShaderI
{
public: // interfaces
	void setUniformValue(const std::string& name, const glm::mat4& value) const override;
	void setUniformValue(const std::string& name, const glm::vec3& value) const override;
	void setUniformValue(const std::string& name, const glm::vec2& value) const override;
	void setUniformValue(const std::string& name, float value) const override;
	void setUniformValue(const std::string& name, int value) const override;
	void setUniformValue(const std::string& name, bool value) const override;
	void setLocationValue(int no, const glm::mat4& value) const override;
	void setLocationValue(int no, const glm::vec3& value) const override;
	void setLocationValue(int no, const glm::vec2& value) const override;
	void setLocationValue(int no, const float& value) const override;
	void setLocationValue(int no, const int& value) const override;
	void setLocationValue(int no, const bool& value) const override;
	void useShaderProgram() const override;

public: // constructor and destructor
	Shader(const std::string& vertexPath, const std::string& fragPath);

	~Shader() override;

private: // member
	std::string vShaderCode;
	std::string fShaderCode;
	const unsigned int id;

private: // private methods
	static unsigned int getUniformLocation(const unsigned id, const std::string& name);
	static std::string getShaderCode(const std::string& shaderPath);
	static int compileShader(const char* shaderCode, unsigned int shaderType);
	static void linkShader(unsigned int id);
public:
	// errors
	/**
	 * \brief err_log is super class of other specific error classes
	 */
	struct err_log : std::runtime_error
	{
	public:
		const char* what() const noexcept override;
		explicit err_log(const char what[BUFSIZ]);
	};
	class err_read_shader_code : public err_log {using err_log::err_log;};
	class err_compile_shader : public err_log {using err_log::err_log;};
	class err_link_shader : public err_log {using err_log::err_log;};
	class err_create_shader : public err_log {using err_log::err_log;};
};


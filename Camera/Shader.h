#pragma once
#include <string>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

/**
 * \brief impl version of ShaderI
 */
class Shader :
    public ShaderI
{
public: // interfaces
	void setUniformValue(std::string name, const glm::mat4& value) const override;
	void setUniformValue(std::string name, const glm::vec3& value) const override;
	void setUniformValue(std::string name, float value) const override;
	void setUniformValue(std::string name, int value) const override;
	void setUniformValue(std::string name, bool value) const override;
	void useShaderProgram() const override;

public: // constructor and destructor
	Shader(std::string vertexPath, std::string fragPath);
	~Shader();

private: // member
	const std::string vShaderCode;
	const std::string fShadercode;

private: // private methods
	unsigned int getUniformLocation(std::string name);
	static std::string getShaderCode(std::string shaderPath);
	static int compileShader(std::string shaderCode, unsigned int shaderType);
	static void linkShader(unsigned int id);

public: // errors
	class err_log
	{
	public:
		const char * what() const;
		err_log(const char* what);
		err_log() {}
	private:
		char what_[512] = "\0";
	};
	class err_read_shader_code : public err_log {};
	class err_compile_shader : public err_log {};
	class err_link_shader : public err_log {};
};


#pragma once

#include <glad/glad.h>		/*include glad to get all the required OpenGL headers*/
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MyShader
{
public:
	GLuint ID; /*program ID*/

	MyShader(const char* vertexPath, const char* fragmentPath);
	~MyShader();
	void useShaderProgram();		/*glUseProgram(ID)*/

	/*all setters query a uniform location and set its value*/
	void setBool(const std::string& name, GLboolean value) const;
	void setInt(const std::string& name, GLint value) const;
	void setFloat(const std::string& name, GLfloat value) const;
	void setMatrix4fv(const std::string& name, const glm::mat4 & value) const;

private:
	const char* vShaderCode;
	const char* fShaderCode;

	std::string getShaderCode(const char* shaderPath) const;
	GLuint compileShader(const char* shaderCode, GLenum shaderType) const;
	void linkShader(const GLuint ID) const;
	GLuint getUniformLocation(const std::string& name) const;

	/*for throwing errors*/
	class err_with_info_log {
	public:
		const char* what();
		err_with_info_log(const char* what);
		err_with_info_log() {};
	private:
		char m_what[512] = "\0";
	};
	class err_read_shader_code: public err_with_info_log {};
	class err_compile_shader: public err_with_info_log {};
	class err_link_shader: public err_with_info_log {};
};


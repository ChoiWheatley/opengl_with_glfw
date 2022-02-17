#include "MyShader.h"
MyShader::MyShader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode, fragmentCode;
	GLuint vertexShader, fragmentShader;
	GLint success=0;
	GLchar infoLog[512]="";

	try
	{
		// 1. retrieve the vertex/fragment source code from filepath
		vertexCode = getShaderCode(vertexPath);
		fragmentCode = getShaderCode(fragmentPath);
		this->vShaderCode = vertexCode.c_str();
		this->fShaderCode = fragmentCode.c_str();


		// 2. Let's compile shaders from shader code
		// print compile errors if any
		vertexShader = compileShader(vShaderCode, GL_VERTEX_SHADER);
		fragmentShader = compileShader(fShaderCode, GL_FRAGMENT_SHADER);


		// 3. attach to a shader Program
		this->ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		//glLinkProgram(ID);
		linkShader(this->ID);
	}
	catch (MyShader::err_read_shader_code& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << '\n';
	}
	catch (MyShader::err_compile_shader& e)
	{
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << e.what() << '\n';
	}
	catch (MyShader::err_link_shader& e)
	{
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << e.what() << '\n';
	}

	// 4. delete the shaders as they're linked into our program now
	// and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

MyShader::~MyShader()
{
	glDeleteShader(ID);
}

void MyShader::useShaderProgram()
{
	glUseProgram(this->ID);
}

/// <summary>
/// Sets a uniform value of the currently active shader program.
/// </summary>
/// <param name="name">: name of the uniform location, which can be
/// retrieved using `glGetUniformLocation`. </param>
/// <param name="value"></param>
void MyShader::setBool(const std::string& name, GLboolean value) const
{
	glUniform1i(
		getUniformLocation(name)
		, (GLint)value
	);
}

void MyShader::setInt(const std::string& name, GLint value) const
{
	glUniform1i(
		getUniformLocation(name)
		, value
	);
}

void MyShader::setFloat(const std::string& name, GLfloat value) const
{
	glUniform1f(
		getUniformLocation(name)
		, value
	);
}

void MyShader::setMatrix4fv(const std::string& name, const glm::mat4 & value) const
{
	glUniformMatrix4fv(
		getUniformLocation(name)
		, 1							/*count*/
		, GL_FALSE					/*transpose*/
		, glm::value_ptr(value)		/*actual matrix data with conversion*/
	);
}

std::string MyShader::getShaderCode(const char* shaderPath) const
{
	std::string ret;
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	// ensure ifstream objects can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(shaderPath);
		//read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// convert stream into string
		ret = shaderStream.str();
		// close file handlers
		shaderFile.close();
	}
	catch (std::ifstream::failure& e)
	{
		//std::cout << e.what() << "\n";
		throw MyShader::err_read_shader_code(e.what());
	}

	return ret;
}

GLuint MyShader::compileShader(const char* shaderCode, GLenum shaderType) const
{
	GLint success;
	GLuint shader;
	char infoLog[512];

	shader = glCreateShader(shaderType);
	if (!shader) {
		std::string report("ERROR::SHADER::CREATION_FAILED");
		throw err_compile_shader(report.c_str());
	}
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	// throw compile errors if any
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw MyShader::err_compile_shader(infoLog);
	}
	return shader;
}

void MyShader::linkShader(const GLuint ID) const
{
	int success;
	char infoLog[512];
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		throw MyShader::err_link_shader(infoLog);
	}
}

GLuint MyShader::getUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(this->ID, name.c_str());
}

const char* MyShader::err_with_info_log::what()
{
	return static_cast<const char*>(m_what);
}

MyShader::err_with_info_log::err_with_info_log(const char* what)
{
	//strcpy(m_what, what);
	strcpy_s(m_what, what);
}

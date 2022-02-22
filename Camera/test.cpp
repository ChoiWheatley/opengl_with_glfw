#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Image.h"
#include "Shader.h"
#include "Constants.h"

#define PRINT_FUNC std::cerr<<"testing..."<<__func__<<'\n'
#define PRINT_SUCCESS std::cerr<<__func__<< " have successed!\n"

static bool image_test();
static bool shader_test();
static GLFWwindow* glfw_init();
/**
 * \brief Image 객체가 올바르게 데이터를 로드하는가?
 * \return 0=올바르게 로드한다. 1=올바르게 로드하지 못한다.
 */
int test_main(int argc, char ** argv)
{
	PRINT_FUNC;
	auto window = glfw_init();
	if (!image_test())
		return 1;
	if (!shader_test())
		return 1;

	while (!glfwWindowShouldClose(window)) {}
	PRINT_SUCCESS;
	return 0;
}

bool image_test()
{
	PRINT_FUNC;
	const Image img{Constants::textures[0].textureFileName.c_str()};
	if (!img.data)
	{
		return false;
	}
	std::cerr << "nrChannel = " << img.nrChannels << '\n';
	std::cerr << "(width, height)= (" << img.width << ", " << img.height << ")\n";

	PRINT_SUCCESS;
	return true;
}

bool shader_test()
{
	PRINT_FUNC;
	std::cerr << __func__ << '\n';
	//TODO: stub model against Shader
	//TODO: implement Shader
	try
	{
		const Shader shader{ Constants::Shader::vertexPath,
			Constants::Shader::fragmentPath };
		shader.useShaderProgram();
		shader.setUniformValue("integer", 0);
		shader.setUniformValue("boolean", true);
		shader.setUniformValue("float", 3.14f);
		shader.setUniformValue("vec3", glm::vec3{ 0.f, 1.f, .5f });
		shader.setUniformValue("mat4", glm::mat4{ 1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
			});
	}
	catch (const Shader::err_log& e)
	{
		std::cout << e.what() << '\n';
		return false;
	}
	PRINT_SUCCESS;
	return true;
}

static void framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height);

GLFWwindow* glfw_init()
{
	PRINT_FUNC;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create a glfw window
	const auto window = glfwCreateWindow(Constants::windowWidth, Constants::windowHeight, Constants::windowName.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	// window viewport should be adjusted when window size is changed.
	/// 별개의 콜백함수 안에서 지역변수/객체에 접근할 수 없다. 전역변수
	/// 말고는 답이 없는걸까?
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// before call opengl functions, tell GLAD to manage function pointers
	// for OpenGL.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		return nullptr;
	}
	// before we can start rendering we have to tell OpenGL the size
	// of the rendering window (ViewPort) so OpenGL knows how we want to
	// display the data and coords with respect to the window.
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	framebuffer_size_callback(window, Constants::windowWidth, Constants::windowHeight);

	PRINT_SUCCESS;
	return window;
}

static void framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height)
{
	PRINT_FUNC;
	glViewport(0, 0, window_width, window_height);
	PRINT_SUCCESS;
}

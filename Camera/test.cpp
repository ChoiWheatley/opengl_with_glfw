#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderFactory.hpp"
#include "ImageFactory.hpp"
#include "TextureFactory.hpp"
#include "vertex_test.hpp"
#include "Stub.h"

static bool image_test();
static bool shader_test();
static bool texture_test();
static GLFWwindow* glfw_init();
/**
 * \brief Image 객체가 올바르게 데이터를 로드하는가?
 * \return 0=올바르게 로드한다. 1=올바르게 로드하지 못한다.
 */
int test_main(int argc, char ** argv)
{
	PRINT_FUNC;
	try
	{
		const auto window = glfw_init();
		if (window == nullptr)
			return 1;
		if (!shader_test())
			return 1;
		if (!image_test())
			return 1;
		if (!texture_test())
			return 1;
		const auto v = VertexTest::testVertexInit();
		if (v == nullptr)
			throw std::runtime_error{"ERROR :: vertex init error!"};
		VertexTest::testVertexBinding(v.get());

		while (!glfwWindowShouldClose(window)) {}
	}
	catch (const std::exception& e)
	{
		std::cerr << typeid(e).name() << " :: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	PRINT_SUCCESS;
	return EXIT_SUCCESS;
}

bool image_test()
{
	PRINT_FUNC;
	const auto img = ImageFactory::make(Stub::texture.textureFileName.c_str());
	if (!img->data)
	{
		throw std::runtime_error{ "image has no data->" };
	}
	std::cerr << "nrChannel = " << img->nrChannels << '\n';
	std::cerr << "(width, height)= (" << img->width << ", " << img->height << ")\n";
	PRINT_SUCCESS;
	return true;
}

bool shader_test()
{
	PRINT_FUNC;
	std::cerr << __func__ << '\n';
	//TODO: stub model against Shader
	//TODO: implement Shader
	const auto shader = ShaderFactory::make(
		Stub::Shader::vertexPath,
		Stub::Shader::fragmentPath
	);
	shader->useShaderProgram();
	shader->setUniformValue("integer", 0);
	shader->setUniformValue("boolean", true);
	shader->setUniformValue("float", 3.14f);
	shader->setUniformValue("vec3", glm::vec3{ 0.f, 1.f, .5f });
	shader->setUniformValue("mat4", glm::mat4{ 1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,
	1.f, 1.f, 1.f, 1.f,
		});
	PRINT_SUCCESS;
	return true;
}

bool texture_test()
{
	PRINT_FUNC;
	static auto filename1 = Stub::texture.textureFileName.c_str();
	const auto texture1 = TextureFactory::make(filename1);
	auto img = ImageFactory::make(filename1);
	const auto texture2 = TextureFactory::make(std::move(img));	// 소유권이 img에서 texture2로 넘어감.
	std::cout << "img has lost own occupant address is : " << img.get() << ". Please don't use this\n";

	texture1->activeTexture();
	texture1->bindTexture();
	texture2->activeTexture();
	texture2->bindTexture();

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
	const auto window = glfwCreateWindow(Stub::windowWidth, Stub::windowHeight, Stub::windowName.c_str(), nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return nullptr;
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
	framebuffer_size_callback(window, Stub::windowWidth, Stub::windowHeight);

	PRINT_SUCCESS;
	return window;
}

static void framebuffer_size_callback(GLFWwindow* window, int window_width, int window_height)
{
	PRINT_FUNC;
	glViewport(0, 0, window_width, window_height);
	PRINT_SUCCESS;
}

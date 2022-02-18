#include <iostream>
#include "Image.h"
#include "Stub.h"
#include "Shader.h"
#include "Constants.h"

#define PRINT_FUNC std::cerr<<"testing..."<<__func__<<'\n';

static bool image_test();
static bool shader_test();
/**
 * \brief Image ��ü�� �ùٸ��� �����͸� �ε��ϴ°�?
 * \return 0=�ùٸ��� �ε��Ѵ�. 1=�ùٸ��� �ε����� ���Ѵ�.
 */
int test_main(int argc, char ** argv)
{
	PRINT_FUNC
	if (!image_test())
		return 1;
	if (!shader_test())
		return 1;
	return 0;
}

bool image_test()
{
	PRINT_FUNC
	const Image img{Stub::Image::filename};
	if (!img.data)
	{
		return false;
	}
	std::cerr << "nrChannel = " << img.nrChannels << '\n';
	std::cerr << "(width, height)= (" << img.width << ", " << img.height << ")\n";

	return true;
}

bool shader_test()
{
	PRINT_FUNC
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
	return true;
}

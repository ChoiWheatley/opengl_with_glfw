#pragma once
#include <vector>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
namespace Stub
{
	constexpr int windowWidth = 800;
	constexpr int windowHeight = 600;
	namespace Camera
	{
		constexpr float aspectRatio = windowWidth / windowHeight;
		constexpr float near = .1f;
		constexpr float far = 100.f;
		constexpr float fov = 45.f;
		constexpr float fovMin = 1.f;
		constexpr float fovMax = 90.f;

		const glm::vec3 initPosition{ 0.f, 0.f, 10.f };
		const glm::vec3 initUp{ 0.f, 1.f, 0.f };
		constexpr float initYaw = -90.f;
		constexpr float initPitch = 0.f;
		constexpr float translationSpeed = 3.1f;
		constexpr float rotationSpeed = .1f;
	}// namespace Camera
	namespace Shader
	{
		constexpr char vertexPath[] = "vertex.vert";
		constexpr char fragmentPath[] = "fragment.frag";
	}// namespace Shader

	namespace Structure
	{
		struct Texture {
			const std::string textureFileName;
			const int textureColorFormat;
		};
		struct RenderState {
			const std::vector<glm::vec3>& cubePositions;
			const std::vector<glm::vec3>& cubeAxis;
			const std::vector<float>& cubeAngles;
			const std::vector<unsigned int>& textures;
			const unsigned int VAO;
		};

	}// namespace Structure
	const std::string windowName = std::string{ "LearnOpenGL" };
	const std::vector< glm::vec3 > cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	const Structure::Texture texture = {.textureFileName = "signup.jpg", .textureColorFormat = GL_RGB};
	constexpr float arcballRotationSpeed = 2.5f;
}
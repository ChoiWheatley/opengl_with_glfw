#pragma once
#include "headers.h"
namespace Constants
{
	constexpr int windowWidth = 800;
	constexpr int windowHeight = 600;
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
	namespace Camera
	{
		constexpr float aspectRatio = windowWidth / windowHeight;
		constexpr float near = .1f;
		constexpr float far = 100.f;
		constexpr float fov = 45.f;
		constexpr float fovMin = 1.f;
		constexpr float fovMax = 90.f;

		constexpr glm::vec3 initPosition{ 0.f, 0.f, 10.f };
		constexpr glm::vec3 initUp{ 0.f, 1.f, 0.f };
		constexpr float initYaw = -90.f;
		constexpr float initPitch = 0.f;
		constexpr float translationSpeed = 0.01f;
		constexpr float rotationSpeed = .1f;
	}// namespace Camera
	struct Texture {
		const std::string textureFileName;
		const int textureColorFormat;
	};
	const std::vector<Texture> textures{
		{"signup.jpg", GL_RGB},
		{"png_with_alpha_channel.png", GL_RGBA}
	};
	namespace Shader
	{
		constexpr char vertexPath[] = "vertex.vert";
		constexpr char fragmentPath[] = "fragment.frag";
	}// namespace Shader

}// namespace Constants

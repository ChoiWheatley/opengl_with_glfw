#pragma once
#include "headers.h"
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

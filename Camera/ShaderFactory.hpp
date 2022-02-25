#pragma once
#include <memory>
#include "Shader.h"

struct ShaderFactory : public ShaderI
{
	static std::unique_ptr<Shader> make(const std::string& vertexPath, const std::string& fragPath)
	{
		return std::make_unique<Shader>(vertexPath, fragPath);
	}
};

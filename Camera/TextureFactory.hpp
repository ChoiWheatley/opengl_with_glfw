#pragma once
#include <memory>
#include "Texture.h"
#include "ImageFactory.hpp"

struct TextureFactory : public TextureI
{
	static std::unique_ptr<Texture> make(const Image& img)
	{
		return std::make_unique<Texture>(img);
	}
	static std::unique_ptr<Texture> make(const char* filename)
	{
		return std::make_unique<Texture>(
			*ImageFactory::make(filename)
			);
	}
};

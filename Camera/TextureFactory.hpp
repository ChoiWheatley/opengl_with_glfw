#pragma once
#include <memory>
#include "Texture.h"
#include "ImageFactory.hpp"

struct TextureFactory : public TextureI
{
	static std::unique_ptr<Texture> make(std::unique_ptr<Image> img)
	{
		return std::make_unique<Texture>(std::move(img));
	}
	static std::unique_ptr<Texture> make(const char* filename)
	{
		return std::make_unique<Texture>(
				ImageFactory::make(filename)
			);
	}
};

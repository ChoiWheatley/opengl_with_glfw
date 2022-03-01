#include <utility>
#include "Texture.h"

const char* Texture::getTextureImg() const
{
	// TODO: ±¸Çö
	return "function `getTextureImg() have to be implemented!";
}

Texture::Texture(std::unique_ptr<Image> img)
	: img_{ std::move(img) }
{
}

Texture::~Texture()
{
	img_.reset();
}

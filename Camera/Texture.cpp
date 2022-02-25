#include <utility>
#include "Texture.h"

const char* Texture::getTextureImg() const
{
	// TODO: ±¸Çö
	return "dddd";
}

Texture::Texture(const Image& img): img{ img }
{}

Texture::~Texture() = default;

#include <utility>
#include "Texture.h"

const char* Texture::getTextureImg() const
{
	// TODO: ����
	return "dddd";
}

Texture::Texture(const Image& img): img{ img }
{}

Texture::~Texture() = default;

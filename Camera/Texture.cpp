#include <utility>
#include "Texture.h"

const char* Texture::getTextureImg() const
{
}

Texture::Texture(const Image& img): img{ img }
{}

// TODO: Factory 패턴을 활용하여 종속성을 관리하자!
Texture::Texture(const char* filename)
	:img{std::move(Image{filename})}
{}

Texture::~Texture() = default;

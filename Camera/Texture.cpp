#include <utility>
#include "Texture.h"

const char* Texture::getTextureImg() const
{
}

Texture::Texture(const Image& img): img{ img }
{}

// TODO: Factory ������ Ȱ���Ͽ� ���Ӽ��� ��������!
Texture::Texture(const char* filename)
	:img{std::move(Image{filename})}
{}

Texture::~Texture() = default;

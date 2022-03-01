#include <utility>
#include <glad/glad.h>
#include "Texture.h"

void Texture::activeTexture() const
{
	glActiveTexture(GL_TEXTURE0 + texture_no);
}

void Texture::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, id_);
}

Texture::Texture(std::unique_ptr<Image> img)
	: img_{ std::move(img) }, channel_(mipmapLv(img_->nrChannels))
{
	///
	/// gen -> active -> bind -> texParameter -> image -> mipmap
	///
	glGenTextures(1, &id_);
	glActiveTexture(GL_TEXTURE0 + texture_no/*TODO: fragment shader에 등록한 텍스쳐 번호를 가져와야 한다.*/);
	glBindTexture(GL_TEXTURE_2D, id_);
	// texture wrapping option -> will be set public member TODO: public member에 파라메터 옵션란 작성하기.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrapping_option_s/*TODO:Texture wrapping option - s*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrapping_option_t/*TODO:Texture wrapping option - t*/);
	// texture filtering option
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter_option_min/*TODO: texture minimum filter option*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter_option_mag/*TODO: texture magnify filter option*/);
	// image data
	glTexImage2D(
		GL_TEXTURE_2D,
		0,/*TODO:mipmap level public val*/
		channel_, img_->width, img_->height,	/*texture attribute*/
		0,	/*unused*/
		channel_, GL_UNSIGNED_BYTE,	
		img_->data	/*actual image data*/
	);
	// generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	// free image
	resetImg(std::move(img_));
	// TODO: tell opengl for sample to which texture unit it belongs
}

Texture::~Texture()
{
	resetImg(std::move(img_));
}

void Texture::resetImg(std::unique_ptr<Image> img)
{
	if (img != nullptr)
		img.reset();
}

int Texture::mipmapLv(int nrChannel)
{
	auto ret = 0;
	// TODO: nrChannel 값이랑 저게 맞는지 확인 필요.
	switch (nrChannel)
	{
	case 4:
		ret = GL_RGBA;
		break;
	case 3:
		ret = GL_RGB;
		break;
	default:
		ret = 0;
	}
	return ret;
}

#pragma once
#include <stb/stb_image.h>
#include "TextureI.h"
#include "Image.h"

class Texture : TextureI
{
public: // interface
	const char* getTextureImg() const override;
public: // constructor
	Texture(const Image& img);
	~Texture() override;
private: // member
	const Image img;
};

#pragma once
#include <stb/stb_image.h>
#include "TextureI.h"
#include "Image.h"

struct Image;

class Texture : TextureI
{
public: // interface
	const char* getTextureImg() const override;
public: // constructor
	Texture(const Image& img) : img{ img } {}
	Texture(const char* filename);
private:
	const Image& img;
};

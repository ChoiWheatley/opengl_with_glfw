#pragma once
#include <memory>
#include "TextureI.h"
#include "Image.h"

class Texture : TextureI
{
public: // interface
	const char* getTextureImg() const override;
public: // constructor
	explicit Texture(std::unique_ptr<Image> img);
	~Texture() override;
private: // member
	std::unique_ptr<Image> img_;
};

#pragma once
#include <memory>
#include "TextureI.h"
#include "Image.h"

class Texture : TextureI
{
public: // interface
	void activeTexture() const override;
	void bindTexture() const override;

public: // constructor
	explicit Texture(std::unique_ptr<Image> img);
	~Texture() override;
public: // public member
	unsigned int texture_no = 0;
	int texture_wrapping_option_s = GL_REPEAT;
	int texture_wrapping_option_t = GL_REPEAT;
	int texture_filter_option_min = GL_LINEAR;
	int texture_filter_option_mag = GL_LINEAR;

private: // member
	std::unique_ptr<Image> img_;
	const int channel_;
	unsigned int id_ = 0;
	static void resetImg(std::unique_ptr<Image> img);
	static int mipmapLv(int nrChannel);
};


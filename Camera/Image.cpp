#include "Image.h"

#include <stb/stb_image.h>
#include "Image.h"

Image::Image(const char* filename)
	: filename(filename)
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (!data)
	{
		throw err_img_load_failed{};
	}
}

Image::~Image()
= default;

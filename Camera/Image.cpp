#include "Image.h"
Image::Image(const char* filename)
	: filename(filename)
{
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(filename, &width, &height, &nrChannels, 0);
}

Image::~Image()
{
	delete data;
}

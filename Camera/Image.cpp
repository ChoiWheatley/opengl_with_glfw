#include "Image.h"
#include <stb/stb_image.h>

Image::Image(const char* filename, bool set_flip_vertically_on_load)
	: filename(filename), set_flip_vertically_on_load(set_flip_vertically_on_load)
{
	stbi_set_flip_vertically_on_load(set_flip_vertically_on_load);
	data = stbi_load(filename, &width, &height, &nrChannels, 0);
}

Image::~Image()
{
	stbi_image_free((void*)data);
	// TODO: 팩토리를 벗어나면 소멸자를 호출하는 이유 파악하기
	// 문제해결: auto a = *ImageFactory::make() 이런 식으로 호출하니 소멸자가 호출된다. *을 제거할 것.
}

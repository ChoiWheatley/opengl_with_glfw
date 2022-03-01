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
	// TODO: ���丮�� ����� �Ҹ��ڸ� ȣ���ϴ� ���� �ľ��ϱ�
	// �����ذ�: auto a = *ImageFactory::make() �̷� ������ ȣ���ϴ� �Ҹ��ڰ� ȣ��ȴ�. *�� ������ ��.
}

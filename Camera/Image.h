#pragma once
#include <exception>
struct Image
{
    Image(const char* filename);
	~Image();

    const char * filename;
    const unsigned char * data;
    int width;
    int height;
    int nrChannels;

	class err_img_load_failed : std::exception{}; // TODO: Error 클래스에서 구현
};


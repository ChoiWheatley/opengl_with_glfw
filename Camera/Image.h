#pragma once
#include <stb/stb_image.h>
struct Image
{
    Image(const char* filename);
	~Image();

    const char * filename;
    const unsigned char * data;
    int width;
    int height;
    int nrChannels;
};


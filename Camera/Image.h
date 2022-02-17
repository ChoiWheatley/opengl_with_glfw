#pragma once
#include "Texture.h"
#include <stb/stb_image.h>
struct Image
{
    Image(const char* filename);

    const char * filename;
    const unsigned char * data;
    int width;
    int height;
    int nrChannels;
};


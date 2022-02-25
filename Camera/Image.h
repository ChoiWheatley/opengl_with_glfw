#pragma once
struct Image
{
    Image(const char* filename);
	~Image();

    const char * filename;
    const unsigned char * data;
    int width;
    int height;
    int nrChannels;

	class err_load_failed{}; // TODO: Error 클래스에서 구현
};


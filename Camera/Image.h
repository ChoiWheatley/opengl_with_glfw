#pragma once
/**
 * \brief Image uses std_images.h to load any image formats with file name.
 */
struct Image
{
	explicit Image(const char* filename, bool set_flip_vertically_on_load = true);
	Image() = default;
	~Image();

	const char* filename = nullptr;
	const unsigned char* data = nullptr;
	int width = 0;
	int height = 0;
	int nrChannels = 0;
	bool set_flip_vertically_on_load = true;
};


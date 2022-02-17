#include <iostream>
#include "Image.h"
#include "Stub.h"
/**
 * \brief Image 객체가 올바르게 데이터를 로드하는가?
 * \return 0=올바르게 로드한다. 1=올바르게 로드하지 못한다.
 */
int test_image_texture_main(int argc, char ** argv)
{
	Image img{Stub::Image::filename};
	if (!img.data)
	{
		return 1;
	}
	std::cerr << "nrChannel = " << img.nrChannels << '\n';
	std::cerr << "(width, height)= (" << img.width << ", " << img.height << ")\n";

	return 0;
}
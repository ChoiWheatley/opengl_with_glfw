#include <iostream>
#include "Image.h"
#include "Stub.h"

static bool image_test();
static bool shader_test();
/**
 * \brief Image 객체가 올바르게 데이터를 로드하는가?
 * \return 0=올바르게 로드한다. 1=올바르게 로드하지 못한다.
 */
int test_main(int argc, char ** argv)
{
	if (image_test())
		return 1;
	return 0;
}

bool image_test()
{
	const Image img{Stub::Image::filename};
	if (!img.data)
	{
		return false;
	}
	std::cerr << "nrChannel = " << img.nrChannels << '\n';
	std::cerr << "(width, height)= (" << img.width << ", " << img.height << ")\n";

	return true;
}

bool shader_test()
{
}

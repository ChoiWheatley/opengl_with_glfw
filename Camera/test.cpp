#include <iostream>
#include "Image.h"
#include "Stub.h"

static bool image_test();
static bool shader_test();
/**
 * \brief Image ��ü�� �ùٸ��� �����͸� �ε��ϴ°�?
 * \return 0=�ùٸ��� �ε��Ѵ�. 1=�ùٸ��� �ε����� ���Ѵ�.
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

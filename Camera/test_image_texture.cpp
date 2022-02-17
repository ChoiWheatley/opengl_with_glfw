#include <iostream>
#include "Image.h"
#include "Stub.h"
/**
 * \brief Image ��ü�� �ùٸ��� �����͸� �ε��ϴ°�?
 * \return 0=�ùٸ��� �ε��Ѵ�. 1=�ùٸ��� �ε����� ���Ѵ�.
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
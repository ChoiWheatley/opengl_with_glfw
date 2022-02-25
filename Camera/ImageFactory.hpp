#pragma once
#include <memory>
#include "Image.h"
struct ImageFactory
{
	static std::unique_ptr<Image> make(const char * filename)
	{
		return std::make_unique<Image>(filename);
	}
};

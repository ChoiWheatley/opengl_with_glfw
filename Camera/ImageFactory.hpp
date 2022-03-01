#pragma once
#include <memory>
#include "Image.h"
struct ImageFactory
{
	static std::unique_ptr<Image> make(const char * filename)
	{
		// TODO: Factory에서 함수를 벗어나면 메모리를 해제해버리는 이유 찾고 문제 해결하자.
		auto ret = std::make_unique<Image>(filename);
		return std::move(ret);
	}
};

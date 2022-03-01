#pragma once
#include <memory>
#include "Image.h"
struct ImageFactory
{
	static std::unique_ptr<Image> make(const char * filename)
	{
		// TODO: Factory���� �Լ��� ����� �޸𸮸� �����ع����� ���� ã�� ���� �ذ�����.
		auto ret = std::make_unique<Image>(filename);
		return std::move(ret);
	}
};

#pragma once
/**
 * \brief image�� ���� �ڷẸ���� ������ ������ �Բ��Ѵ�.
 * \dependency stb_image�� ���� �����Լ����� �����ϴ� �Ļ�� ��ü
 */
class TextureI
{
public: // interfaces
	virtual const char* getTextureImg() const = 0;

	virtual ~TextureI() = default;
};

#pragma once
/**
 * \brief image�� ���� �ڷẸ���� ������ ������ �Բ��Ѵ�.
 * \dependency stb_image�� ���� �����Լ����� �����ϴ� �Ļ�� ��ü
 */
class TextureI
{
public: // interfaces
	virtual void activeTexture() const = 0;
	virtual void bindTexture() const = 0;

	virtual ~TextureI() = default;
};

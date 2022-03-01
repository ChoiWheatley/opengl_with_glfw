#pragma once
/**
 * \brief image에 대한 자료보관과 데이터 제공을 함께한다.
 * \dependency stb_image에 대한 전역함수들을 래핑하는 파사드 객체
 */
class TextureI
{
public: // interfaces
	virtual void activeTexture() const = 0;
	virtual void bindTexture() const = 0;

	virtual ~TextureI() = default;
};

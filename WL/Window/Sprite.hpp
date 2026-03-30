//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_SPRITE_HPP
#define WINLIB_SPRITE_HPP
#include <WL/Core/Core.hpp>
#include <WL/Window/Drawable.hpp>
#include <WL/Window/Texture.hpp>
#include <WL/Core/Vector.hpp>
WL_NAMESPACE_BEGIN
class Sprite : public Drawable {
	Texture _Texture;
public:
	Sprite(const Texture& texture);
	void setTexture(const Texture& texture);
	const Texture& getTexture() const;
private:
	void _CreateBitmap(HDC& _CrHdc, const Texture& _Tex, bool ism, bool isconstructor);
};
WL_NAMESPACE_END
#endif //WINLIB_SPRITE_HPP
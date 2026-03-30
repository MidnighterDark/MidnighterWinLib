//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_DRAWABLE_HPP
#define WINLIB_DRAWABLE_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Vector.hpp>
#include <WL/Core/Rect.hpp>
#include <WL/Window/Window.hpp>
WL_NAMESPACE_BEGIN
class Drawable {
	friend class Window;
protected:
	Vector2i _Pos;
	Vector2i _Size;
	Vector2i _Root;
	Vector2f _Scale;
	IntRect _Rect;
	HDC _Hdc = NULL;
	HDC _MaskHdc = NULL;
	HBITMAP _hHdcBitmap = NULL;
	HBITMAP _hOldHdcBitmap = NULL;
	~Drawable();
public:
	Vector2i getPosition() const;
	Vector2f getScale() const;
	Vector2i getRoot() const;
	Vector2i getSize() const;
	IntRect getGlobalBounds() const;
	void setPosition(Int32 x, Int32 y);
	void setScale(float x, float y);
	void setSize(Int32 x, Int32 y);
	void setRoot(Int32 x, Int32 y);
};
WL_NAMESPACE_END
#endif //WINLIB_DRAWABLE_HPP
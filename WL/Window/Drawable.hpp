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
	Vector2i _Orgin;
	Vector2f _Scale;
	float	 _LastAngle;
	float    _Angle;
	IntRect  _Rect;
	HDC      _Hdc =				NULL;
	HDC      _MaskHdc =			NULL;
	HDC		 _AngleHdc =		NULL;
	HDC		 _AngleMaskHdc =	NULL;
	HBITMAP  _hHdcBitmap =		NULL;
	HBITMAP  _hOldHdcBitmap =	NULL;
	WINLIB_API ~Drawable();
public:
	//For get element's position
	WINLIB_API Vector2i getPosition() const;
	//For get element's scale
	WINLIB_API Vector2f getScale() const;
	//For get element's root
	WINLIB_API Vector2i getRoot() const;
	//For get element's orgin
	WINLIB_API Vector2i getOrgin() const;
	//For get element's size
	WINLIB_API Vector2i getSize() const;
	//For get element's global bounds in IntRect
	WINLIB_API IntRect  getGlobalBounds() const;
	//For get element's rotation
	WINLIB_API float    getAngle() const;
	//For setting element's global position
	WINLIB_API void     setPosition(Int32 x, Int32 y);
	//Overriding setPosition and adding an argument as a Vector2i
	WINLIB_API void     setPosition(Vector2i pos);
	//For setting element's scale
	WINLIB_API void     setScale(float x, float y);
	//Overriding setScale and adding an argument as a Vector2f
	WINLIB_API void     setScale(Vector2f scale);
	//To adjust the size of an element in pixels
	//If the pixel size is smaller than the image size, the image will crop all pixels outside the area
	WINLIB_API void     setSize(Int32 x, Int32 y);
	//Overriding setSize and adding an argument as a Vector2i
	WINLIB_API void     setSize(Vector2i size);
	//For setting element's root
	WINLIB_API void     setRoot(Int32 x, Int32 y);
	//Overriding setRoot and adding an argument as a Vector2i
	WINLIB_API void     setRoot(Vector2i root);
	//For setting element's orgin
	WINLIB_API void     setOrgin(Int32 x, Int32 y);
	//Overriding setOrgin and adding an argument as a Vector2i
	WINLIB_API void     setOrgin(Vector2i root);
	//For setting element's rotation
	WINLIB_API void     setAngle(float newAngle);
};
WL_NAMESPACE_END
#endif //WINLIB_DRAWABLE_HPP
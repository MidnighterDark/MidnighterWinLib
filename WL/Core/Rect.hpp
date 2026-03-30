//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_RECT_HPP
#define WINLIB_RECT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Vector.hpp>
WL_NAMESPACE_BEGIN
template<typename T>
class Rect {
public:
	T top;
	T bottom;
	T left;
	T right;
	Rect() = default;
	Rect(T right, T top, T left, T bottom)
		: right(right), top(top), left(left), bottom(bottom)
	{

	}
	//To determine whether a given position is within the rectangle.
	bool contains(Vector2i pos) const;
};
typedef Rect<Int32> IntRect;
typedef Rect<float> FloatRect;
template<typename T>
bool Rect<T>::contains(Vector2i pos) const
{
	if (pos.x >= right && pos.x <= (right + left) && pos.y >= top && pos.y <= (top + bottom))
		return true;
	return false;
}
WL_NAMESPACE_END
#endif //WINLIB_RECT_HPP
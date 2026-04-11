//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_RECT_HPP
#define WINLIB_RECT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Vector.hpp>
WL_NAMESPACE_BEGIN
//Rect::top is the top of the element in global coordinates
//Rect::left is the left of the element in global coordinates
//Rect::bottom is the local size in the Y coordinate
//Rect::right is the local size at the X coordinate
template<typename T>
class Rect {
public:
	T top;
	T bottom;
	T left;
	T right;
	Rect() = default;
	Rect(T left, T top, T right, T bottom)
		: left(left), top(top), right(right), bottom(bottom)
	{

	}
	//To determine whether a given position is within the rectangle.
	bool contains(Vector2i pos) const;
};
//IntRect::top is the top of the element in global coordinates
//IntRect::left is the left of the element in global coordinates
//IntRect::right is the right of the element in global coordinates
//IntRect::bottom is the bottom of the element in global coordinates
typedef Rect<Int32> IntRect;
//FloatRect::top is the top of the element in global coordinates
//FloatRect::left is the left of the element in global coordinates
//FloatRect::right is the right of the element in global coordinates
//FloatRect::bottom is the bottom of the element in global coordinates
typedef Rect<float> FloatRect;
//
template<typename T>
bool Rect<T>::contains(Vector2i pos) const
{
	if (pos.x >= left && pos.y >= top && pos.x <= right && pos.y <= bottom)
		return true;
	return false;
}
WL_NAMESPACE_END
#endif //WINLIB_RECT_HPP
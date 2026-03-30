//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_VECTOR_HPP
#define WINLIB_VECTOR_HPP
#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
template<typename T> class Vector2 {
public:
	T x;
	T y;
	Vector2() = default;
	Vector2(T f, T t) : x(f), y(t) {}
	bool operator==(const Vector2& varifable) const;
};
template<typename T>
bool Vector2<T>::operator==(const Vector2& varifable) const
{
	return (x == varifable.x && y == varifable.y);
}
typedef Vector2<Int32> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
WL_NAMESPACE_END
#endif // WINLIB_VECTOR_HPP
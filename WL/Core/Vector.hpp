//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_VECTOR_HPP
#define WINLIB_VECTOR_HPP
#include <WL/Core/Core.hpp>
#include <cmath>
WL_NAMESPACE_BEGIN
template<typename T> 
class Vector2 {
	float length;
public:
	T x;
	T y;
	Vector2() = default;
	Vector2(T f, T t) : x(f), y(t) {}
	void	Append(const Vector2<T>& addedVec);
	float	Length() const;
	bool	operator==(const Vector2<T>& varifable) const;
};
template<typename T>
inline void Vector2<T>::Append(const Vector2<T>& addedVec)
{
	x += addedVec.x;
	y += addedVec.y;
	length = std::sqrt((x * x) + (y * y));
}
template<typename T>
float Vector2<T>::Length() const
{
	return length;
}
template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& varifable) const 
{
	return (x == varifable.x && y == varifable.y);
}
typedef Vector2<Int32>	Vector2i;
typedef Vector2<float>	Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2i		vec2i;
typedef Vector2f		vec2f;
typedef Vector2d		vec2d;
WL_NAMESPACE_END
#endif // WINLIB_VECTOR_HPP
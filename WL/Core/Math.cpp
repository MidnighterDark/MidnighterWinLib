#include <WL/Core/Math.hpp>
#undef __max
#undef __min
WL_NAMESPACE_BEGIN
template<typename T>
inline T __max(T a, T b) {
	if (a >= b)
		return a;
	else if (b > a)
		return b;
	return 0;
}
template<typename T>
inline T __min(T a, T b) {
	if (a <= b)
		return a;
	else if (b < a)
		return b;
	return 0;
}
math::f32 math::clamp(f32 val, f32 min, f32 max)
{
	if (val >= max)
		return max;
	else if (val <= min)
		return min;
	else 
		return val;
}
math::f32 math::avoid(f32 val, f32 begin_border, f32 border_end)
{
	if (val < begin_border) {
		return val;
	}
	else if (val > border_end) {
		return val;
	}
	else {
		f32 t = (border_end - begin_border) / 2;
		if (val > t) {
			return border_end;
		}
		else if (val <= t) {
			return begin_border;
		}
	}
	return -1;
}
math::f32 math::ndegree(f32 degree, char _Ty)
{
	switch (_Ty)
	{
	case N180DG: {
		if (degree > 180) {
			i32 _re = 180.f * (f32(degree / 180) - i32(degree / 180.f));
			return 0 - (180 - _re);
		}
		else if (degree < -180) {
			i32 _re = 180.f * (f32((degree * -1.f) / 180) - i32((degree * -1.f) / 180));
			return (180 - _re);
		}
		else {
			return degree;
		}
		break;
	}
	case N360DG: {
		if (degree > 360) {
			i32 _re = 360.f * (f32(degree / 360.f) - i32(degree / 360.f));
			return _re;
		}
		else if (degree < 0) {
			i32 _re = 360.f * (f32((degree * -1) / 360) - i32((degree * -1) / 360));
			return (360 - _re);
		}
		else {
			return degree;
		}
		break;
	}
	}
	return -1;
}
math::i32 math::max(i32 first, i32 second)
{
	return __max<i32>(first, second);
}
math::i32 math::min(i32 first, i32 second)
{
	return __min<i32>(first, second);
}
math::f32 math::max(f32 first, f32 second)
{
	return __max<f32>(first, second);
}
math::f32 math::min(f32 first, f32 second)
{
	return __min<f32>(first, second);
}
math::i64 math::max(i64 first, i64 second)
{
	return __max<i64>(first, second);
}
math::i64 math::min(i64 first, i64 second)
{
	return __min<i64>(first, second);
}
WL_NAMESPACE_END


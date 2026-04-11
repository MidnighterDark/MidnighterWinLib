#include <WL/Core/Math.hpp>
WL_NAMESPACE_BEGIN
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
math::f32 math::max(f32 first, f32 second)
{
	if (first >= second)
		return first;
	else if (second > first)
		return second;
	return 0;
}
math::f32 math::min(f32 first, f32 second)
{
	if (first <= second)
		return first;
	else if (second < first)
		return second;
	return 0;
}
WL_NAMESPACE_END


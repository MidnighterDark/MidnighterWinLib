//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_MATH
#define WINLIB_MATH
#include <WL/Core/Core.hpp>

//WARNING!!!
//BETA TEST!!!
//IN DEVELOPMENT!!!

#define N180DG			0x00
#define N360DG			0x01

WL_NAMESPACE_BEGIN
namespace math {
	namespace normalizedegree {
		enum {
			NormalizeTo180 = N180DG,
			NormalizeTo360 = N360DG,
		};
	}
	typedef float		f32;
	typedef double		d32;
	typedef long double	d64; //Not always 64???
	typedef Int32		i32;

	inline extern f32 	WINLIB_API clamp(f32 val, f32 min, f32 max);
	inline extern f32	WINLIB_API avoid(f32 val, f32 begin_border, f32 border_end);
	inline extern f32	WINLIB_API ndegree(f32 degree, char type);
	inline extern f32	WINLIB_API max(f32 first, f32 second);
	inline extern f32	WINLIB_API min(f32 first, f32 second);
}
WL_NAMESPACE_END
#endif //WINLIB_MATH
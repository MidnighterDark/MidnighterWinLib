//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_COLOR_HPP
#define WINLIB_COLOR_HPP
#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
struct rgba {
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	Uint8 a = 255;
	Bool operator<(Uint8 val);
	Bool operator>(Uint8 val);
};
class Color {
	Uint8 _R;
	Uint8 _G;
	Uint8 _B;
	Uint8 _A;
	Uint32 _Data;
public:
	Color() = delete;
	~Color() = default;
	Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255) : _R(r), _G(g), _B(b), _A(a) 
	{
		_Data = ((Uint32)a << 24) | ((Uint32)r << 16) | ((Uint32)g << 8) | ((Uint32)b);
	}
	const Uint32 getData() const { return _Data; }
	rgba getColor() const {
		rgba _Re;
		_Re.r = _R;
		_Re.g = _G;
		_Re.b = _B;
		_Re.a = _A;
		return _Re;
	}
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
};
WL_NAMESPACE_END
#endif //WINLIB_COLOR_HPP
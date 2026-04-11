//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_COLOR_HPP
#define WINLIB_COLOR_HPP
#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
struct WINLIB_API rgba {
	//This is a red channel
	Uint8 r = 0;
	//This is a green channel
	Uint8 g = 0;
	//This is a blue channel
	Uint8 b = 0;
	//This is a alpha channel
	Uint8 a = 255;
	Bool operator<(Uint8 val);
	Bool operator>(Uint8 val);
};
class WINLIB_API Color {
	Uint8 _R;
	Uint8 _G;
	Uint8 _B;
	Uint8 _A;
	Uint32 _Data;
public:
	Color() = delete;
	~Color() = default;
	//This constructor setting rgb and alpha channel
	Color(Uint8 val, Uint8 alpha);
	//In this constructor you mast setting all parametrs
	Color(Uint8 r, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
	//Return Uint32 data
	const Uint32 getData() const;
	//Return rgba of color
	const rgba	 getColor() const;
	//Default white color
	static const Color White;
	//Default black color
	static const Color Black;
	//Default red color
	static const Color Red;
	//Default green color
	static const Color Green;
	//Default blue color
	static const Color Blue;
};
WL_NAMESPACE_END
#endif //WINLIB_COLOR_HPP
//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_TEXTURE_HPP
#define WINLIB_TEXTURE_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Container.hpp>
#include <WL/Core/Color.hpp>
#include <WL/Core/Vector.hpp>
#include <WL/Core/String.hpp>
WL_NAMESPACE_BEGIN
class WINLIB_API Texture {
	container<Uint32>	_Pixels;
	Uint16				_Width;
	Uint16				_Height;
public:
	//For create texture and paint color them
	void		create(const Color& color, Uint16 width, Uint16 height);
	//For load custom format
	//Read more at https://midnighterdark.github.io/MidnighterWinLib
	void		loadFromTDF(String _Path);
	//For load BMP 24-bit file
	void		loadFromBMP(String _Path);
	//For load png file
	void		loadFromPNG(String _Path);
	//For get width, height.
	Vector2i	getSize() const { return Vector2i(_Width, _Height); }
	//For get Uint32* pixels array
	Uint32*	    getPixelsData() const { return _Pixels.data(); }
	//For get pixels quantity
	Uint32		getPixelsSize() const { return _Pixels.size(); }
	/*and more*/
	void		operator=(const Texture& val);
	bool		operator==(const Texture& verifable) const;
	bool		operator!=(const Texture& verifable) const;
};
WL_NAMESPACE_END
#endif //WINLIB_TEXTURE_HPP
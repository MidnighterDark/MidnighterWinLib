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
class Texture {
	container<Uint32> _Pixels;
	Uint16 _Width;
	Uint16 _Height;
public:
	void create(const Color& color, Uint16 width, Uint16 height);
	void loadFromTDF(String _Path);
	void loadFromBMP(String _Path);
	void loadFromPNG(String _Path);
	Vector2i getSize() const { return Vector2i(_Width, _Height); }
	Uint32* getPixelsData() const { return _Pixels.data(); }
	Uint32 getPixelsSize() const { return _Pixels.size(); }
	void operator=(const Texture& val);
	bool operator==(const Texture& verifable) const;
	bool operator!=(const Texture& verifable) const;
};
WL_NAMESPACE_END
#endif //WINLIB_TEXTURE_HPP
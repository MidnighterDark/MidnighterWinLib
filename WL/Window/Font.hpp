//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_FONT_HPP
#define WINLIB_FONT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/String.hpp>
#include <WL/Core/Container.hpp>
WL_NAMESPACE_BEGIN
class Font {
	String _FontFamalyName;
	String _Path;
public:
	Font() = default;
	~Font();
	bool loadFromFile(String path);
	String getFontFamalyName() const;
	static const Font DefaultOS;
};
WL_NAMESPACE_END
#endif //WINLIB_FONT_HPP
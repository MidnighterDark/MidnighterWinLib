//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_FONT_HPP
#define WINLIB_FONT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/String.hpp>
#include <WL/Core/Container.hpp>
WL_NAMESPACE_BEGIN
class WINLIB_API Font {
	String _FontFamalyName = "Arial";
	String _Path;
public:
	Font() = default;
	Font(String fontFamalyName);
	~Font();
	//Load from TTF (True Type Font) file
	bool   loadFromFile(String path);
	//For get Font Famaly's name
	String getFontFamalyName() const;
	//Default font
	static const Font DefaultOS;
};
WL_NAMESPACE_END
#endif //WINLIB_FONT_HPP
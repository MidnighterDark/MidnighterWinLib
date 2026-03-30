//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_TEXT_HPP
#define WINLIB_TEXT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Color.hpp>
#include <WL/Core/String.hpp>
#include <WL/Window/Drawable.hpp>
#include <WL/Window/Font.hpp>
WL_NAMESPACE_BEGIN
//For edit text style.
struct TextStyle {
	//Makes the text slanted.
	Bool Italic = 0;
	//Underlines the text.
	Bool Underline = 0;
	//Makes the text strike out
	Bool StrikeOut = 0;
	TextStyle() 
		: Italic(0), Underline(0), StrikeOut(0) {}
	TextStyle(Bool bItalic, Bool bUnderline, Bool bStrikeOut) 
		: Italic(bItalic), Underline(bUnderline), StrikeOut(bStrikeOut) {}
};
class Text : public Drawable {
	String _Text;
	Font _Font;
	Uint16 _FontSize;
	Color _Color = Color(0, 0, 0);
	TextStyle _TextStyle = TextStyle();
public:
	Text(const String& text, const Font& font, Uint16 fontSize, Color color = Color(0, 0, 0), const TextStyle& tStyle = TextStyle());
	void setText(const String& text);
	void setFont(const Font& font);
	void setFontSize(Uint16 fontSize);
	void setTextStyle(const TextStyle& newStyle);
	String getText() const;
	Font getFont() const;
	Uint16 getFontSize() const;
private:
	void _CreateTextHDC(HDC& hdc, const String& text, const Font& font, Uint16 fontSize, COLORREF colorref, bool isconstructor, const TextStyle& tStyle, bool ispw = true);
};
WL_NAMESPACE_END
#endif //WINLIB_TEXT_HPP
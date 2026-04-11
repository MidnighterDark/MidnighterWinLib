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
//Character weight
namespace FontWeights {
	enum {
		Dontcare = 0,
		Thin = 100,
		Extralight = 200,
		Light = 300,
		Normal = 400,
		Medium = 500,
		Semibold = 600,
		Bold = 700,
		Extrabold = 800,
		Heavy = 900,
	};
}
//For edit text style.
struct TextStyle {
	//Makes the text slanted.
	Bool	Italic		= 0;
	//Underlines the text.
	Bool	Underline	= 0;
	//Makes the text strike out
	Bool	StrikeOut	= 0;
	//Font Weights
	Uint32	Weights		= FontWeights::Normal;
	//Constructors
	TextStyle() 
		: Italic(0), Underline(0), StrikeOut(0) {}
	TextStyle(Bool bItalic, Bool bUnderline, Bool bStrikeOut) 
		: Italic(bItalic), Underline(bUnderline), StrikeOut(bStrikeOut) {}
};
class Text : public Drawable {
	String		_Text;
	Font		_Font;
	Uint16		_FontSize;
	Color		_Color = Color::Black;
	TextStyle	_TextStyle = TextStyle();
	Bool		_BackgroundTransparent;
	Color		_BackgroundColor = Color::Black;
public:
	//Constructor
	WINLIB_API Text(const String& text, const Font& font, Uint16 fontSize, Color color = Color(0, 0, 0), const TextStyle& tStyle = TextStyle());
	//This function replaces the current text with a new one.
	WINLIB_API void		setText(const String& text);
	//This function replaces the current font with a new one.
	WINLIB_API void		setFont(const Font& font);
	//This function for setting character's size
	WINLIB_API void		setFontSize(Uint16 fontSize);
	//This function for setting text style whith struct "wl::TextStyle"
	WINLIB_API void		setTextStyle(const TextStyle& newStyle);
	//This function for setting text's background
	WINLIB_API void		setBackground(bool isTransparent, const Color& color);
	//For get current text
	WINLIB_API String		getText() const;
	//For get current font
	WINLIB_API Font		getFont() const;
	//For get current character size (ignore default font's size)
	WINLIB_API Uint16		getFontSize() const;
	//For get text style
	WINLIB_API TextStyle	getTextStyle() const;
private:
	void		_CreateTextHDC(HDC& hdc, const String& text, const Font& font, Uint16 fontSize, COLORREF colorref, bool isconstructor, const TextStyle& tStyle, bool ispw = true);
};
WL_NAMESPACE_END
#endif //WINLIB_TEXT_HPP
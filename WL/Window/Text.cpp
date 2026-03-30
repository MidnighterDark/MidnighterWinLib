#include <WL/Window/Text.hpp>
#include <iostream>
WL_NAMESPACE_BEGIN
Text::Text(const String& text, const Font& font, Uint16 fontSize, Color color, const TextStyle& tStyle)
{
    _TextStyle = tStyle;
    _CreateTextHDC(_MaskHdc, text, font, fontSize, RGB(0, 0, 0), true, tStyle);
    _CreateTextHDC(_Hdc, text, font, fontSize, RGB(color.getColor().r, color.getColor().g, color.getColor().b), true, tStyle, false);
    _Text = text;
    _Font = font;
    _FontSize = fontSize;
    _Color = color;
}
void Text::setText(const String& text)
{
    _Text = text.getWideString().c_str();
    _CreateTextHDC(_MaskHdc, _Text, _Font, _FontSize, RGB(0, 0, 0), false, _TextStyle, true);
    _CreateTextHDC(_Hdc, _Text, _Font, _FontSize, RGB(_Color.getColor().r, _Color.getColor().g, _Color.getColor().b), false, _TextStyle, false);
}
void Text::setFont(const Font& font)
{
    _Font = font;
    _CreateTextHDC(_MaskHdc, _Text, _Font, _FontSize, RGB(0, 0, 0), false, _TextStyle, true);
    _CreateTextHDC(_Hdc, _Text, _Font, _FontSize, RGB(_Color.getColor().r, _Color.getColor().g, _Color.getColor().b), false, _TextStyle, false);
}
void Text::setFontSize(Uint16 fontSize)
{
    _FontSize = fontSize;
    _CreateTextHDC(_MaskHdc, _Text, _Font, _FontSize, RGB(0, 0, 0), false, _TextStyle, true);
    _CreateTextHDC(_Hdc, _Text, _Font, _FontSize, RGB(_Color.getColor().r, _Color.getColor().g, _Color.getColor().b), false, _TextStyle, false);
}
void Text::setTextStyle(const TextStyle& newStyle)
{
    _TextStyle = newStyle;
    _CreateTextHDC(_MaskHdc, _Text, _Font, _FontSize, RGB(0, 0, 0), false, _TextStyle, true);
    _CreateTextHDC(_Hdc, _Text, _Font, _FontSize, RGB(_Color.getColor().r, _Color.getColor().g, _Color.getColor().b), false, _TextStyle, false);
}
String Text::getText() const
{
    return _Text;
}
Font Text::getFont() const
{
    return _Font;
}
Uint16 Text::getFontSize() const
{
    return _FontSize;
}
void Text::_CreateTextHDC(HDC& _CrHdc, const String& text, const Font& font, Uint16 fontSize, COLORREF colorref, bool isconstructor, const TextStyle& tStyle, bool ispw)
{
    HFONT hFont = CreateFontW(
        fontSize,
        0,
        0,
        0,
        FW_NORMAL,
        tStyle.Italic,
        tStyle.Underline,
        tStyle.StrikeOut,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        font.getFontFamalyName().getLpcwstr()
    );
    //Initialization HDC
    HDC hdc = GetDC(Core::GetHwndRef());
    if (_CrHdc != NULL) {
        DeleteObject(_CrHdc);
    }
    _CrHdc = CreateCompatibleDC(hdc);

    //Save old font and select new
    HFONT hOldFont = (HFONT)SelectObject(_CrHdc, hFont);

    //Get size of text
    SIZE textSize = { 0 };
    GetTextExtentPoint32(_CrHdc, text.getLpcwstr(), text.getWideString().length(), &textSize);
    Uint16 width = textSize.cx;
    Uint16 height = textSize.cy;
    _Size = Vector2i(width, height);

    if (isconstructor) {
        _Pos = Vector2i(0, 0);
        _Scale = Vector2f(1.0f, 1.0f);
        _Root = Vector2i(0, 0);
    }
    _Rect = IntRect(_Pos.x, _Pos.y, width, height);

    //Create hBitmap
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = width * height * 4;
    
    if (_hHdcBitmap != NULL) {
        if (_hOldHdcBitmap == NULL) {
            std::cerr << "ERROR: Text: Drawable::_hHdcBitmap != NULL when Drawable::_hOldHdcBitmap == NULL!!!\n";
            return;
        }
        SelectObject(_Hdc, _hOldHdcBitmap);
        DeleteObject(_hHdcBitmap);
    }
    _hHdcBitmap = CreateDIBSection(_CrHdc, &bmi, DIB_RGB_COLORS, nullptr, NULL, 0);

    
    //Select hBitmap to _CrHdc
    _hOldHdcBitmap = (HBITMAP)SelectObject(_CrHdc, _hHdcBitmap);
    
    //
    if (ispw) {
        HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH hOldWhiteBrush = (HBRUSH)SelectObject(_CrHdc, hWhiteBrush);
        PatBlt(_CrHdc, 0, 0, width, height, PATCOPY);
        SelectObject(_CrHdc, hOldWhiteBrush);
        DeleteObject(hWhiteBrush);
    }

    //Set style
    SetBkColor(_CrHdc, RGB(0, 0, 0));
    SetBkMode(_CrHdc, TRANSPARENT);
    SetTextColor(_CrHdc, colorref);

    //Draw text in HDC
    TextOut(_CrHdc, 0, 0, text.getLpcwstr(), text.getWideString().length());

    SelectObject(_CrHdc, hOldFont);
    DeleteObject(hFont);
    ReleaseDC(Core::GetHwndRef(), hdc);
}
WL_NAMESPACE_END
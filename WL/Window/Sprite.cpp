#include <WL/Window/Sprite.hpp>
#include <iostream>
WL_NAMESPACE_BEGIN
void Sprite::_CreateBitmap(HDC& _CrHdc, const Texture& _Tex, bool ism, bool isconstructor)
{
    if (isconstructor) {
        _Pos = Vector2i(0, 0);
        _Scale = Vector2f(1.0f, 1.0f);
        _Root = Vector2i(0, 0);
    }
    _Rect = IntRect(_Pos.x, _Pos.y, _Pos.x + _Tex.getSize().x, _Pos.y + _Tex.getSize().y);
    _Size = Vector2i(_Tex.getSize().x, _Tex.getSize().y);

    //Create BITMAPINFO
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biWidth = _Tex.getSize().x;
    bmi.bmiHeader.biHeight = _Tex.getSize().y;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = _Tex.getSize().x * _Tex.getSize().y * 4;

    //Initialization HDC
    HDC hdc = GetDC(Core::GetHwndRef(0));
    if (_CrHdc != NULL) {
        DeleteObject(_CrHdc);
    }
    _CrHdc = CreateCompatibleDC(hdc);
    ReleaseDC(Core::GetHwndRef(0), hdc);

    if (_hHdcBitmap != NULL) {
        if (_hOldHdcBitmap == NULL) {
            std::cerr << "ERROR: Sprite: Drawable::_hHdcBitmap != NULL when Drawable::_hOldHdcBitmap == NULL!!!\n";
            return;
        }
        SelectObject(_Hdc, _hOldHdcBitmap);
        DeleteObject(_hHdcBitmap);
    }
    //Create bitmap
    void* pPixels = nullptr;
    _hHdcBitmap = CreateDIBSection(_CrHdc, &bmi, DIB_RGB_COLORS, &pPixels, nullptr, 0);

    if (ism) {
        //Create mask
        for (Uint32 i = 0; i < _Tex.getPixelsSize(); i++) {
            Uint32 alpha = (_Tex.getPixelsData()[i] >> 24) & 0xFF;
            Uint32 maskValue = (alpha > 0) ? 0x00000000 : 0xFFFFFFFF;
            static_cast<Uint32*>(pPixels)[i] = maskValue;
        }
    }
    else {
        //Base color
        memcopy<Uint32>(static_cast<Uint32*>(pPixels), _Tex.getPixelsData(), _Tex.getPixelsSize());
    }
    //
    _hOldHdcBitmap = (HBITMAP)SelectObject(_CrHdc, _hHdcBitmap);

}
Sprite::Sprite(const Texture& texture)
{
    _Texture = texture;
    _CreateBitmap(_MaskHdc, texture, true, true);
    _CreateBitmap(_Hdc, texture, false, true);
}
void Sprite::setTexture(const Texture& texture)
{
    _Texture = texture;
    _CreateBitmap(_MaskHdc, texture, true, false);
    _CreateBitmap(_Hdc, texture, false, false);
}
const Texture& Sprite::getTexture() const
{
    return _Texture;
}
WL_NAMESPACE_END
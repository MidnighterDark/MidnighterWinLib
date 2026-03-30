#include <WL/Window/Drawable.hpp>
WL_NAMESPACE_BEGIN
Drawable::~Drawable()
{
    if (_Hdc != NULL) {
        SelectObject(_Hdc, _hOldHdcBitmap);
        DeleteObject(_hHdcBitmap);
        ReleaseDC(Core::GetHwndRef(), _Hdc);
    }
    if (_MaskHdc != NULL) {
        ReleaseDC(Core::GetHwndRef(), _MaskHdc);
    }
}
Vector2i Drawable::getPosition() const
{
    return _Pos;
}
Vector2f Drawable::getScale() const
{
    return _Scale;
}
Vector2i Drawable::getRoot() const
{
    return _Root;
}
Vector2i Drawable::getSize() const
{
    return _Size;
}
IntRect Drawable::getGlobalBounds() const
{
    return _Rect;
}
void Drawable::setPosition(Int32 x, Int32 y)
{
    _Pos = Vector2i(x, y);
    _Rect = IntRect(x, y, _Rect.left, _Rect.bottom);
}
void Drawable::setScale(float x, float y)
{
    _Scale = Vector2f(x, y);
    _Rect = IntRect(_Pos.x, _Pos.y, _Size.x * x, _Size.y * y);
}
void Drawable::setSize(Int32 x, Int32 y)
{
    _Size = Vector2i(x, y);
    _Rect = IntRect(_Pos.x, _Pos.y, _Scale.x * x, _Scale.y * y);
}
void Drawable::setRoot(Int32 x, Int32 y)
{
    _Root = Vector2i(x, y);
}
WL_NAMESPACE_END
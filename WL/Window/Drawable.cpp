#include <WL/Window/Drawable.hpp>
WL_NAMESPACE_BEGIN
Drawable::~Drawable()
{
    if (_Hdc != NULL) {
        SelectObject(_Hdc, _hOldHdcBitmap);
        DeleteObject(_hHdcBitmap);
        DeleteDC(_Hdc);
    }
    if (_MaskHdc != NULL) {
        DeleteDC(_MaskHdc);
    }
    if (_AngleMaskHdc != NULL) {
        DeleteDC(_AngleMaskHdc);
    }
    if (_AngleHdc != NULL) {
        DeleteDC(_AngleHdc);
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
Vector2i Drawable::getOrgin() const
{
    return _Orgin;
}
Vector2i Drawable::getSize() const
{
    return _Size;
}
IntRect Drawable::getGlobalBounds() const
{
    return _Rect;
}
float Drawable::getAngle() const
{
    return _Angle;
}
void Drawable::setPosition(Int32 x, Int32 y)
{
    _Pos = Vector2i(x, y);
}
void Drawable::setPosition(Vector2i p)
{
    _Pos = Vector2i(p.x, p.y);
}
void Drawable::setScale(float x, float y)
{
    _Scale = Vector2f(x, y);
}
void Drawable::setScale(Vector2f s)
{
    _Scale = Vector2f(s.x, s.y);
}
void Drawable::setSize(Int32 x, Int32 y)
{
    _Size = Vector2i(x, y);
}
void Drawable::setSize(Vector2i s)
{
    _Size = Vector2i(s.x, s.y);
}
void Drawable::setRoot(Int32 x, Int32 y)
{
    _Root = Vector2i(x, y);
}
void Drawable::setRoot(Vector2i r)
{
    _Root = Vector2i(r.x, r.y);
}
void Drawable::setOrgin(Int32 x, Int32 y)
{
    _Orgin = Vector2i(x, y);
}
void Drawable::setOrgin(Vector2i root)
{
    _Orgin = root;
}
void Drawable::setAngle(float a)
{
    _Angle = a;
}
WL_NAMESPACE_END
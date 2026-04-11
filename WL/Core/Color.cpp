#include "Color.hpp"
WL_NAMESPACE_BEGIN
Bool rgba::operator<(Uint8 val)
{
    if (r > val && g > val && b > val)
        return 0;
    else if (r != val && g != val && b != val)
        return 1;
    else
        return 0;
}
Bool rgba::operator>(Uint8 val)
{
    if (r < val && g < val && b < val)
        return 0;
    else if (r != val && g != val && b != val)
        return 1;
    else
        return 0;
}
Color::Color(Uint8 val, Uint8 alpha) : _R(val), _G(val), _B(val), _A(alpha)
{
    _Data = ((Uint32)alpha << 24) | ((Uint32)val << 16) | ((Uint32)val << 8) | ((Uint32)val);
}
Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : _R(r), _G(g), _B(b), _A(a)
{
    _Data = ((Uint32)a << 24) | ((Uint32)r << 16) | ((Uint32)g << 8) | ((Uint32)b);
}
const Uint32 Color::getData() const
{
    return _Data;
}
const rgba Color::getColor() const
{
    rgba _Re;
    _Re.r = _R;
    _Re.g = _G;
    _Re.b = _B;
    _Re.a = _A;
    return _Re;
}
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
WL_NAMESPACE_END
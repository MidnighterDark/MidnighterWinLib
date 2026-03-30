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
const Color Color::White(255, 255, 255, 255);
const Color Color::Black(0, 0, 0, 255);
const Color Color::Red(255, 0, 0, 255);
const Color Color::Green(0, 255, 0, 255);
const Color Color::Blue(0, 0, 255, 255);
WL_NAMESPACE_END
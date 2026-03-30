#include <WL/Core/Event.hpp>
#include <Windows.h>
WL_NAMESPACE_BEGIN
Vector2i Mouse::getGlobalMousePos()
{
	POINT _CursorPoint;
	GetCursorPos(&_CursorPoint);
	return Vector2i(_CursorPoint.x, _CursorPoint.y);
}
bool Event::isPressed(Key::Type key) const
{
	return keyState[key];
}
bool(&Event::getKeyState())[256]
{
	return keyState;
}
WL_NAMESPACE_END
#include <WL/Core/Event.hpp>
#include <Windows.h>
#include <thread>
WL_NAMESPACE_BEGIN
Vector2i Mouse::getGlobalMousePos()
{
	POINT _CursorPoint;
	GetCursorPos(&_CursorPoint);
	return Vector2i(_CursorPoint.x, _CursorPoint.y);
}
bool Mouse::isButtonPressed(Buttons::Type key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;;
}
bool isButtonPressed(Key::Type key)
{
	return (GetAsyncKeyState(key) & 0x8000) != 0;
}
void Event::simulateKeyPress(Key::Type key, Uint32 delay, bool isCreateNewThread)
{
    if (isCreateNewThread == true) {
        std::thread t([key, delay]() {
            INPUT input = { 0 };
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = key;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));
            Core::Delay(delay);
            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
            });
        t.detach();
    }
    else {
        INPUT input = { 0 };
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = key;
        input.ki.dwFlags = 0;
        SendInput(1, &input, sizeof(INPUT));
        Core::Delay(delay);
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}
WL_NAMESPACE_END
//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_WINDOW_HPP
#define WINLIB_WINDOW_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Event.hpp>
#include <WL/Core/String.hpp>
#include <WL/Core/Vector.hpp>
#include <WL/Window/Drawable.hpp>
#include <WL/Core/Color.hpp>
#include <WL/Core/Container.hpp>
#include <WL/Core/Math.hpp>

WL_NAMESPACE_BEGIN
//Style of window.
namespace Style {
	enum {
		Default = 13628088,
		DefaultNoResize = 13238272,
		Border = -2147483648,
		Fullscreen = -1879048192,
	};
};
//For setting window's position and size.
struct WINLIB_API WindowTransform {
	Int32 posX;
	Int32 posY;
	Int32 sizeX;
	Int32 sizeY;
	WindowTransform() = default;
	WindowTransform(Int32 px, Int32 py, Int32 sx, Int32 sy) : posX(px), posY(py), sizeX(sx), sizeY(sy) {}
};
//This class for create window.
class Window {
	friend class Drawable;
	friend LRESULT CALLBACK WinProc(HWND _Hwnd, UINT _Msg, WPARAM _WParam, LPARAM _LpParam);
	WindowTransform _WindowTransform;
public:
	Window() = delete;
	WINLIB_API Window(WindowTransform transform, String title, Uint64 style = Style::Default);

	//Returns whether the window is open.
	WINLIB_API bool		isOpen();

	//For setting window's title.
	WINLIB_API void		setTitle(String newTytle);
	//For setting window's icon.
	WINLIB_API void		setIcon(Uint32* pixelsData, Uint32 width, Uint32 height);
	//To set the cursor as long as it is in the current window.
	WINLIB_API void		setCursor(Uint32* pixelsData, Uint32 width, Uint32 height, Vector2i hotPos = Vector2i(0, 0));

	//To get cursor position in the current window.
	WINLIB_API Vector2i	getLocalMousePos() const;
	//To set local cursor's position
	WINLIB_API void		setLocalCursorPos(Int32 x, Int32 y);

	//To listen for window events.
	WINLIB_API void		listenEvents(Event& event);
	//To clean the window and paint it.
	WINLIB_API void		clear(const Color& clr);
	//To draw something on buffer.
	WINLIB_API void		draw(Drawable& something);
	//To draw picture from buffer and draw it in the window.
	WINLIB_API void		display() const;
	//To close current window.
	WINLIB_API void		close();
	//To limit fps whith error rate ~3fps.
	WINLIB_API void		fpsLimiter(Uint16 fps);

	//To get current window's position.
	WINLIB_API Vector2i	getPosition() const;
	//To get current window's size.
	WINLIB_API Vector2i	getSize() const;
	//For setting window's screen position
	WINLIB_API void		setPosition(Int32 x, Int32 y);
	//For setting window's size
	WINLIB_API void		setSize(Int32 x, Int32 y);

	//To get current window's title.
	WINLIB_API String	getTitle() const;
private:
	Uint16			_WindowIndex;
	Event*			_Event;
	//Window varibles
	HINSTANCE		_HandleInstance;
	WNDCLASSEX		_Wc;
	LPCWSTR			_ClassName = L"mWinLib";
	LPCWSTR			_WindowTitle = L"WinLib";
	BOOL			_IsOpen;
	rgba			_ClearerColor;
	LARGE_INTEGER	_Freq, _StTick;
	//m - memory
	HBITMAP			_mWindowHDC_Bitmap;
	HBITMAP			_Old_mWindowHDC_Bitmap;
	RECT			_ClientRect;
	HCURSOR			_CurrentWindowCursor;
	HICON			_CurrentSmallIcon;
	HICON			_CurrentBiglIcon;
};
WL_NAMESPACE_END
#endif //WINLIB_WINDOW_HPP
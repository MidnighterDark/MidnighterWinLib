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
struct WindowTransform {
	Int32 _PosX;
	Int32 _PosY;
	Int32 _SizeX;
	Int32 _SizeY;
	WindowTransform() = default;
	WindowTransform(Int32 _Px, Int32 _Py, Int32 _Sx, Int32 _Sy) : _PosX(_Px), _PosY(_Py), _SizeX(_Sx), _SizeY(_Sy) {}
};
//This class for create window.
class Window {
	friend class Drawable;
	friend LRESULT CALLBACK WinProc(HWND _Hwnd, UINT _Msg, WPARAM _WParam, LPARAM _LpParam);
	WindowTransform _WindowTransform;
public:
	Window() = delete;
	Window(WindowTransform _Wparm, String _Title, Uint64 _Style = Style::Default);

	//Returns whether the window is open.
	bool isOpen();

	//For setting window's title.
	void setTitle(String newTytle);
	//For setting window's icon.
	void setIcon(Uint32* pixelsData, Uint32 width, Uint32 height);
	//To set the cursor as long as it is in the current window.
	void setCursor(Uint32* pixelsData, Uint32 width, Uint32 height, Vector2i hotPos = Vector2i(0, 0));

	//To get cursor position in the current window.
	Vector2i getLocalMousePos() const;

	//To listen for window events.
	void listenEvents(Event& event);
	//To clean the window and paint it.
	void clear(const Color& clr);
	//To draw something on buffer.
	void draw(Drawable& something);
	//To draw picture from buffer and draw it in the window.
	void display() const;
	//To close current window.
	void close();
	//To limit fps whith error rate ~3fps.
	void fpsLimiter(Uint16 fps);

	//To get current window's position.
	Vector2i getPosition() const;
	//To get current window's size.
	Vector2i getSize() const;

	//To get current window's title.
	String getTitle() const;
private:
	Uint8 _WindowIndex;

	Event* _Event;
	//Window varibles
	HINSTANCE _HandleInstance;
	WNDCLASSEX _Wc;
	LPCWSTR _ClassName = L"mWinLib";
	LPCWSTR _WindowTitle = L"WinLib";
	BOOL _IsOpen;
	rgba _ClearerColor;
	LARGE_INTEGER _Freq, _StTick;
	//m - memory
	HBITMAP _mWindowHDC_Bitmap;
	HBITMAP _Old_mWindowHDC_Bitmap;
	RECT _ClientRect;
	HCURSOR _CurrentWindowCursor;
	HICON _CurrentSmallIcon;
	HICON _CurrentBiglIcon;

};
WL_NAMESPACE_END
#endif //WINLIB_WINDOW_HPP
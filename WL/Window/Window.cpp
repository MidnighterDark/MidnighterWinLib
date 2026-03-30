#include <WL/Window/Window.hpp>
#include <thread>
#include <chrono> 
#include <iostream>
WL_NAMESPACE_BEGIN

Window* _WinProcCurrentWindow;
LRESULT CALLBACK WinProc(HWND _Hwnd, UINT _Msg, WPARAM _WParam, LPARAM _LpParam)
{
	if (_WinProcCurrentWindow != nullptr) {
		switch (_Msg)
		{
		case WM_KEYDOWN: {
			if (_WinProcCurrentWindow->_Event)
				_WinProcCurrentWindow->_Event->getKeyState()[Uint16(_WParam)] = true;
			break;
		}
		case WM_KEYUP: {
			_WinProcCurrentWindow->_Event->getKeyState()[Uint16(_WParam)] = false;
			break;
		}
		case WM_CLOSE: {
			_WinProcCurrentWindow->_Event->type = Event::Closed;
			break;
		}
		case WM_SIZE: {
			if (_WinProcCurrentWindow->_Event)
				_WinProcCurrentWindow->_Event->type = Event::Resized;
			GetClientRect(_Hwnd, &_WinProcCurrentWindow->_ClientRect);
			if (_WinProcCurrentWindow->_mWindowHDC_Bitmap != NULL) {
				SelectObject(Core::GetMemHdcRef(), _WinProcCurrentWindow->_Old_mWindowHDC_Bitmap);
				DeleteObject(_WinProcCurrentWindow->_Old_mWindowHDC_Bitmap);
				_WinProcCurrentWindow->_mWindowHDC_Bitmap = NULL;
			}
			HDC _TempHDC = GetDC(_Hwnd);
			_WinProcCurrentWindow->_mWindowHDC_Bitmap = CreateCompatibleBitmap(_TempHDC, _WinProcCurrentWindow->_ClientRect.right + 10, _WinProcCurrentWindow->_ClientRect.bottom + 10);
			ReleaseDC(_Hwnd, _TempHDC);
			SelectObject(Core::GetMemHdcRef(), _WinProcCurrentWindow->_mWindowHDC_Bitmap);
			break;
		}
		}
	}
	return DefWindowProc(_Hwnd, _Msg, _WParam, _LpParam);
}
Window::Window(WindowTransform _Wparm, String _Title, Uint64 _Style)
{
	_WindowTransform = _Wparm;
	SetProcessDPIAware();
	QueryPerformanceFrequency(&_Freq);
	_HandleInstance = GetModuleHandle(NULL);
	_Wc = { 0 };
	_Wc.cbSize = sizeof(_Wc);
	_Wc.hInstance = _HandleInstance;
	_Wc.lpfnWndProc = WinProc;
	_Wc.lpszClassName = _ClassName;
	_Wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

	RegisterClassEx(&_Wc);

	_WindowTitle = _Title.getLpcwstr();

	Uint32 _SX = _Wparm._SizeX;
	Uint32 _SY = _Wparm._SizeY;
	if (_Style == Style::Fullscreen) {
		_SX = GetSystemMetrics(SM_CXSCREEN);
		_SY = GetSystemMetrics(SM_CYSCREEN);
	}
	Core::GetHwndRef() = CreateWindowEx(
		0,
		_ClassName,
		_WindowTitle,
		_Style,
		_Wparm._PosX, _Wparm._PosY, _SX, _SY,
		NULL, NULL, _HandleInstance, NULL
	);

	ShowWindow(Core::GetHwndRef(), SW_SHOW);

	_IsOpen = 1;

	GetClientRect(Core::GetHwndRef(), &_ClientRect);
	HDC _TempHDC = GetDC(Core::GetHwndRef());
	Core::GetMemHdcRef() = CreateCompatibleDC(_TempHDC);
	_mWindowHDC_Bitmap = CreateCompatibleBitmap(_TempHDC, _ClientRect.right, _ClientRect.bottom);
	_Old_mWindowHDC_Bitmap = (HBITMAP)SelectObject(Core::GetMemHdcRef(), _mWindowHDC_Bitmap);
	ReleaseDC(Core::GetHwndRef(), _TempHDC);
}
bool Window::isOpen()
{
	QueryPerformanceCounter(&_StTick);
	return _IsOpen;
}
void Window::setTitle(String _NewTytle)
{
	SetWindowText(Core::GetHwndRef(), _NewTytle.getLpcwstr());
}
void Window::setIcon(Uint32* _Pixels, Uint32 width, Uint32 height)
{
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	HDC hdcScreen = GetDC(Core::GetHwndRef());
	void* bits = nullptr;
	HBITMAP hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
	memcpy(bits, _Pixels, width * height * sizeof(unsigned int));
	ICONINFO iconInfo = { 0 };
	iconInfo.fIcon = 1;
	iconInfo.xHotspot = width / 2;
	iconInfo.yHotspot = height / 2;
	iconInfo.hbmMask = hBitmap;
	iconInfo.hbmColor = hBitmap;
	HICON hIcon = CreateIconIndirect(&iconInfo);
	DeleteObject(hBitmap);
	ReleaseDC(Core::GetHwndRef(), hdcScreen);
	if (_CurrentBiglIcon != NULL) {
		DestroyIcon(_CurrentBiglIcon);
	}
	if (_CurrentSmallIcon != NULL) {
		DestroyIcon(_CurrentSmallIcon);
	}
	_CurrentBiglIcon = reinterpret_cast<HICON>(SendMessage(Core::GetHwndRef(), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon)));
	_CurrentSmallIcon = reinterpret_cast<HICON>(SendMessage(Core::GetHwndRef(), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon)));
	SetWindowPos(Core::GetHwndRef(), nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}
void Window::setCursor(Uint32* _Pixels, Uint32 width, Uint32 height, Vector2i hotPos)
{
	//Get Window DC. NO RELEASE!!!
	HDC hdc = GetDC(Core::GetHwndRef());

	//Create mask for mouse cursor.
	Uint32* pMaskPixels = new Uint32[width * height+1];
	for (Uint32 i = 0; i < (width * height); i++) {
		if ((_Pixels[i] & 0xFF000000) == 0 || (_Pixels[i] & 0x00FFFFFF) >= 0x00FFFFFF) {
			pMaskPixels[i] = 0xFFFFFFFF;
		}
		else {
			pMaskPixels[i] = 0x00000000;
		}
	}

	//Create BITMAPINFO for mask.
	BITMAPINFO mbmi = { 0 };
	mbmi.bmiHeader.biSize = sizeof(mbmi);
	mbmi.bmiHeader.biWidth = width;
	mbmi.bmiHeader.biHeight = height;
	mbmi.bmiHeader.biBitCount = 32;
	mbmi.bmiHeader.biPlanes = 1;
	mbmi.bmiHeader.biSizeImage = (width*height)*32;
	mbmi.bmiHeader.biCompression = BI_RGB;

	//Create mask bitmap
	void* pMaskPixelsMem = nullptr;
	HBITMAP maskBitmap = CreateDIBSection(hdc, &mbmi, NULL, &pMaskPixelsMem, NULL, NULL);
	memcopy<Uint32>(static_cast<Uint32*>(pMaskPixelsMem), pMaskPixels, (width * height));

	//Create BITMAPINFO for base color.
	BITMAPINFO bcbmi = { 0 };
	bcbmi.bmiHeader.biSize = sizeof(bcbmi);
	bcbmi.bmiHeader.biWidth = width;
	bcbmi.bmiHeader.biHeight = height;
	bcbmi.bmiHeader.biBitCount = 32;
	bcbmi.bmiHeader.biPlanes = 1;
	bcbmi.bmiHeader.biSizeImage = (width * height) * 4;
	bcbmi.bmiHeader.biCompression = BI_RGB;

	//Create base color bitmap
	void* pBaseColorPixelsMem = nullptr;
	HBITMAP baseColorBitmap = CreateDIBSection(hdc, &bcbmi, NULL, &pBaseColorPixelsMem, NULL, NULL);
	for (Uint32 i = 0; i < (width * height); i++) {
		if ((_Pixels[i] & 0xFFFFFFFF) >= 0xFFFFFFFF) {
			static_cast<Uint32*>(pBaseColorPixelsMem)[i] = 0x00000000;
		}
		else {
			static_cast<Uint32*>(pBaseColorPixelsMem)[i] = _Pixels[i];
		}
	}

	ICONINFO ii = { 0 };
	ii.fIcon = 0;
	ii.hbmColor = baseColorBitmap;
	ii.hbmMask = maskBitmap;
	ii.xHotspot = hotPos.x;
	ii.yHotspot = hotPos.y;

	//Destroy cursor if cursor valid
	if (_CurrentWindowCursor != NULL) {
		DestroyCursor(_CurrentWindowCursor);
	}

	_CurrentWindowCursor = (HCURSOR)CreateIconIndirect(&ii);

	SetClassLongPtr(Core::GetHwndRef(), GCLP_HCURSOR, (LONG_PTR)_CurrentWindowCursor);

	//Release DC / Delete objects
	ReleaseDC(Core::GetHwndRef(), hdc);
	DeleteObject(maskBitmap);
	DeleteObject(baseColorBitmap);
}
Vector2i Window::getLocalMousePos() const
{
	POINT _CursorPoint;
	GetCursorPos(&_CursorPoint);
	ScreenToClient(Core::GetHwndRef(), &_CursorPoint);
	return Vector2i(_CursorPoint.x, _CursorPoint.y);
}
void Window::listenEvents(Event& event)
{
	_WinProcCurrentWindow = this;
	_Event = &event;
	event.type = Event::None;
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			_IsOpen = false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}
}
void Window::draw(Drawable& _DrawClass)
{
	StretchBlt(
		Core::GetMemHdcRef(),
		_DrawClass._Pos.x - _DrawClass._Root.x,
		_DrawClass._Pos.y - _DrawClass._Root.y,
		_DrawClass._Size.x * _DrawClass._Scale.x,
		_DrawClass._Size.y * _DrawClass._Scale.y,
		_DrawClass._MaskHdc,
		0, 0,
		_DrawClass._Size.x,
		_DrawClass._Size.y,
		SRCAND
	);
	StretchBlt(
		Core::GetMemHdcRef(),
		_DrawClass._Pos.x - _DrawClass._Root.x,
		_DrawClass._Pos.y - _DrawClass._Root.y,
		_DrawClass._Size.x * _DrawClass._Scale.x,
		_DrawClass._Size.y * _DrawClass._Scale.y,
		_DrawClass._Hdc,
		0, 0,
		_DrawClass._Size.x,
		_DrawClass._Size.y,
		SRCPAINT
	);
}
void Window::display() const
{
	HDC _wDC = GetDC(Core::GetHwndRef());
	BitBlt(_wDC, 0, 0, _ClientRect.right, _ClientRect.bottom, Core::GetMemHdcRef(), 0, 0, SRCCOPY);
	ReleaseDC(Core::GetHwndRef(), _wDC);
}
void Window::close()
{
	if (Core::GetHwndRef() == NULL)
		return;

	DestroyWindow(Core::GetHwndRef());
	Core::GetHwndRef() = NULL;
	_Event->type = Event::Closed;
	_IsOpen = false;
}
void Window::clear(const Color& clr)
{
	_ClearerColor = clr.getColor();
	RECT _Rect = { 0, 0, _ClientRect.right, _ClientRect.bottom };
	HBRUSH _Brush = CreateSolidBrush(RGB(_ClearerColor.r, _ClearerColor.g, _ClearerColor.b));
	FillRect(Core::GetMemHdcRef(), &_Rect, _Brush);
	DeleteObject(_Brush);
}
void Window::fpsLimiter(Uint16 fps)
{
	LARGE_INTEGER _EndFrame;
	QueryPerformanceCounter(&_EndFrame);
	Int64 millisecs = ((_EndFrame.QuadPart - _StTick.QuadPart) * 1000) / _Freq.QuadPart;
	if (millisecs < (1000 / (fps * 2))) {
		std::this_thread::sleep_for(std::chrono::milliseconds((1000 / Uint16(fps * 2)) - millisecs));
	}
}
Vector2i Window::getPosition() const
{
	return Vector2i(_WindowTransform._PosX, _WindowTransform._PosY);
}
Vector2i Window::getSize() const
{
	return Vector2i(_WindowTransform._SizeX, _WindowTransform._SizeY);
}
String Window::getTitle() const
{
	return _WindowTitle;
}
WL_NAMESPACE_END
#include <WL/Window/Window.hpp>
#include <thread>
#include <chrono> 
#include <iostream>
WL_NAMESPACE_BEGIN

LRESULT CALLBACK WinProc(HWND _Hwnd, UINT _Msg, WPARAM _WParam, LPARAM _LpParam)
{
	Window* pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(_Hwnd, GWLP_USERDATA));
	if (pWindow != nullptr && pWindow->_Event != nullptr) {
		switch (_Msg)
		{
		case WM_CLOSE: {
			pWindow->_Event->type = Event::Closed;
			break;
		}
		case WM_SIZE: {
			if (pWindow->_Event)
				pWindow->_Event->type = Event::Resized;
			GetClientRect(_Hwnd, &pWindow->_ClientRect);
			if (pWindow->_mWindowHDC_Bitmap != NULL) {
				SelectObject(Core::GetMemHdcRef(pWindow->_WindowIndex), pWindow->_Old_mWindowHDC_Bitmap);
				DeleteObject(pWindow->_mWindowHDC_Bitmap);
				pWindow->_mWindowHDC_Bitmap = NULL;
			}
			HDC _TempHDC = GetDC(_Hwnd);
			pWindow->_mWindowHDC_Bitmap = CreateCompatibleBitmap(_TempHDC, pWindow->_ClientRect.right + 10, pWindow->_ClientRect.bottom + 10);
			ReleaseDC(_Hwnd, _TempHDC);
			SelectObject(Core::GetMemHdcRef(pWindow->_WindowIndex), pWindow->_mWindowHDC_Bitmap);
			break;
		}
		}
	}
	return DefWindowProc(_Hwnd, _Msg, _WParam, _LpParam);
}
Window::Window(WindowTransform _Wparm, String _Title, Uint64 _Style)
{

	_WindowIndex = Core::GetWindowQuantity();
	Core::GetWindowQuantity()++;

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

	Uint32 _SX = _Wparm.sizeX;
	Uint32 _SY = _Wparm.sizeY;
	if (_Style == Style::Fullscreen) {
		_SX = GetSystemMetrics(SM_CXSCREEN);
		_SY = GetSystemMetrics(SM_CYSCREEN);
	}
	Core::GetHwndRef(_WindowIndex) = CreateWindowEx(
		0,
		_ClassName,
		_WindowTitle,
		_Style,
		_Wparm.posX, _Wparm.posY, _SX, _SY,
		NULL, NULL, _HandleInstance, NULL
	);

	SetWindowLongPtr(Core::GetHwndRef(_WindowIndex), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(Core::GetHwndRef(_WindowIndex), SW_SHOW);

	_IsOpen = 1;

	GetClientRect(Core::GetHwndRef(_WindowIndex), &_ClientRect);
	HDC _TempHDC = GetDC(Core::GetHwndRef(_WindowIndex));
	Core::GetMemHdcRef(_WindowIndex) = CreateCompatibleDC(_TempHDC);
	_mWindowHDC_Bitmap = CreateCompatibleBitmap(_TempHDC, _ClientRect.right, _ClientRect.bottom);
	_Old_mWindowHDC_Bitmap = (HBITMAP)SelectObject(Core::GetMemHdcRef(_WindowIndex), _mWindowHDC_Bitmap);
	ReleaseDC(Core::GetHwndRef(_WindowIndex), _TempHDC);
}
bool Window::isOpen()
{
	QueryPerformanceCounter(&_StTick);
	return _IsOpen;
}
void Window::setTitle(String _NewTytle)
{
	SetWindowText(Core::GetHwndRef(_WindowIndex), _NewTytle.getLpcwstr());
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
	HDC hdcScreen = GetDC(Core::GetHwndRef(_WindowIndex));
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
	ReleaseDC(Core::GetHwndRef(_WindowIndex), hdcScreen);
	if (_CurrentBiglIcon != NULL) {
		DestroyIcon(_CurrentBiglIcon);
	}
	if (_CurrentSmallIcon != NULL) {
		DestroyIcon(_CurrentSmallIcon);
	}
	_CurrentBiglIcon = reinterpret_cast<HICON>(SendMessage(Core::GetHwndRef(_WindowIndex), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon)));
	_CurrentSmallIcon = reinterpret_cast<HICON>(SendMessage(Core::GetHwndRef(_WindowIndex), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon)));
	SetWindowPos(Core::GetHwndRef(_WindowIndex), nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}
void Window::setCursor(Uint32* _Pixels, Uint32 width, Uint32 height, Vector2i hotPos)
{
	//Get Window DC. NO RELEASE!!!
	HDC hdc = GetDC(Core::GetHwndRef(_WindowIndex));

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

	SetClassLongPtr(Core::GetHwndRef(_WindowIndex), GCLP_HCURSOR, (LONG_PTR)_CurrentWindowCursor);

	//Release DC / Delete objects
	ReleaseDC(Core::GetHwndRef(_WindowIndex), hdc);
	DeleteObject(maskBitmap);
	DeleteObject(baseColorBitmap);
}
Vector2i Window::getLocalMousePos() const
{
	POINT _CursorPoint;
	GetCursorPos(&_CursorPoint);
	ScreenToClient(Core::GetHwndRef(_WindowIndex), &_CursorPoint);
	return Vector2i(_CursorPoint.x, _CursorPoint.y);
}
void Window::setLocalCursorPos(Int32 x, Int32 y)
{
	SetCursorPos(_WindowTransform.posX + x, _WindowTransform.posY + y);
}
void Window::listenEvents(Event& event)
{
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
	Uint32	safeSize = static_cast<Uint32>(math::max((_DrawClass._Size.x * _DrawClass._Scale.x), (_DrawClass._Size.y * _DrawClass._Scale.y) + math::max(_DrawClass._Orgin.x, _DrawClass._Orgin.y)) * 1.42f) + 2;
	Uint32	newSafeSize = safeSize * 2;

	if (_DrawClass._Angle != _DrawClass._LastAngle || (_DrawClass._AngleMaskHdc == NULL && _DrawClass._AngleHdc == NULL)) {

		if (_DrawClass._AngleMaskHdc != NULL)
			DeleteDC(_DrawClass._AngleMaskHdc);
		if (_DrawClass._AngleHdc != NULL)
			DeleteDC(_DrawClass._AngleHdc);

		math::ndegree(_DrawClass._Angle, N180DG);

		//rad, sin, cos
		float rad = _DrawClass._Angle * (PI / 180.f);
		float vcos = cos(rad);
		float vsin = sin(rad);

		//Init DC
		HDC hdc =						GetDC(Core::GetHwndRef(_WindowIndex));
		_DrawClass._AngleHdc =			CreateCompatibleDC(hdc);
		_DrawClass._AngleMaskHdc =		CreateCompatibleDC(hdc);

		//Create and select bitmaps
		HBITMAP hBitmap =				CreateCompatibleBitmap(hdc, newSafeSize, newSafeSize);
		HBITMAP hMaskBitmap =			CreateCompatibleBitmap(hdc, newSafeSize, newSafeSize);
		HBITMAP hOldBitmap =			(HBITMAP)SelectObject(_DrawClass._AngleHdc, hBitmap);
		HBITMAP hMaskOldBitmap =		(HBITMAP)SelectObject(_DrawClass._AngleMaskHdc, hMaskBitmap);

		//Paint white brush
		HBRUSH hBrush =					CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH hOldBrush =				(HBRUSH)SelectObject(_DrawClass._AngleMaskHdc, hBrush);
		PatBlt(_DrawClass._AngleMaskHdc, 0, 0, newSafeSize, newSafeSize, PATCOPY);
		SelectObject(_DrawClass._AngleMaskHdc, hOldBrush);
		DeleteObject(hBrush);

		//w, h
		Uint32 width =					_DrawClass._Size.x * _DrawClass._Scale.x;
		Uint32 height =					_DrawClass._Size.y * _DrawClass._Scale.y;

		//Creating points and their positions.
		POINT vertex[3];
		vertex[0] =						{ static_cast<long>(safeSize - (_DrawClass._Orgin.x * vcos) + (_DrawClass._Orgin.y * vsin)),static_cast<long>(safeSize - (_DrawClass._Orgin.x * vsin) - (_DrawClass._Orgin.y * vcos) - 0.5f) };
		vertex[1] =						{ static_cast<long>((_DrawClass._Size.x * _DrawClass._Scale.x) * vcos) + static_cast<long>(safeSize - (_DrawClass._Orgin.x * vcos) + (_DrawClass._Orgin.y * vsin)),static_cast<long>((_DrawClass._Size.x * _DrawClass._Scale.x) * vsin) + static_cast<long>(safeSize - (_DrawClass._Orgin.x * vsin) - (_DrawClass._Orgin.y * vcos)) };
		vertex[2] =						{ -static_cast<long>((_DrawClass._Size.y * _DrawClass._Scale.y) * vsin) + static_cast<long>(safeSize - (_DrawClass._Orgin.x * vcos) + (_DrawClass._Orgin.y * vsin)), static_cast<long>((_DrawClass._Size.y * _DrawClass._Scale.y) * vcos) + static_cast<long>(safeSize - (_DrawClass._Orgin.x * vsin) - (_DrawClass._Orgin.y * vcos) - 0.5f) };

		//Rectangle collision
		POINT fpoint;
		fpoint.x =						safeSize + ((width * vcos) - (height * vsin)) - (_DrawClass._Orgin.x * vcos) + (_DrawClass._Orgin.y * vsin);
		fpoint.y =						safeSize + (height * vcos) + (width * vsin) - (_DrawClass._Orgin.y * vcos) - (_DrawClass._Orgin.x * vsin);
		_DrawClass._Rect = IntRect(
			_DrawClass._Pos.x + math::min(math::min(vertex[0].x, vertex[2].x), math::min(vertex[1].x, fpoint.x)) - safeSize - _DrawClass._Root.x,
			_DrawClass._Pos.y + math::min(math::min(vertex[0].y, vertex[2].y), math::min(vertex[1].y, fpoint.y)) - safeSize - _DrawClass._Root.y,
			_DrawClass._Pos.x + math::max(math::max(vertex[0].x, vertex[2].x), math::max(vertex[1].x, fpoint.x)) - safeSize - _DrawClass._Root.x,
			_DrawClass._Pos.y + math::max(math::max(vertex[0].y, vertex[2].y), math::max(vertex[1].y, fpoint.y)) - safeSize - _DrawClass._Root.y
		);

		//Copy image whith rotation
		PlgBlt(_DrawClass._AngleMaskHdc, vertex, _DrawClass._MaskHdc, 0, 0, _DrawClass._Size.x, _DrawClass._Size.y, NULL, 0, 0);
		PlgBlt(_DrawClass._AngleHdc, vertex, _DrawClass._Hdc, 0, 0, _DrawClass._Size.x, _DrawClass._Size.y, NULL, 0, 0);

		//Free resource
		ReleaseDC(Core::GetHwndRef(_WindowIndex), hdc);
		DeleteObject(hBitmap);
		DeleteObject(hMaskBitmap);

		_DrawClass._LastAngle =			_DrawClass._Angle;
	}
	//Draw
	StretchBlt(
		Core::GetMemHdcRef(_WindowIndex),
		_DrawClass._Pos.x - safeSize - _DrawClass._Root.x,
		_DrawClass._Pos.y - safeSize - _DrawClass._Root.y,
		newSafeSize,
		newSafeSize,
		_DrawClass._AngleMaskHdc,
		0, 0,
		newSafeSize,
		newSafeSize,
		SRCAND
	);
	StretchBlt(
		Core::GetMemHdcRef(_WindowIndex),
		_DrawClass._Pos.x - safeSize - _DrawClass._Root.x,
		_DrawClass._Pos.y - safeSize - _DrawClass._Root.y,
		newSafeSize,
		newSafeSize,
		_DrawClass._AngleHdc,
		0, 0,
		newSafeSize,
		newSafeSize,
		SRCPAINT
	);
}
void Window::display() const
{
	HDC _wDC = GetDC(Core::GetHwndRef(_WindowIndex));
	BitBlt(_wDC, 0, 0, _ClientRect.right, _ClientRect.bottom, Core::GetMemHdcRef(_WindowIndex), 0, 0, SRCCOPY);
	ReleaseDC(Core::GetHwndRef(_WindowIndex), _wDC);
}
void Window::close()
{
	if (Core::GetHwndRef(_WindowIndex) == NULL)
		return;

	DestroyWindow(Core::GetHwndRef(_WindowIndex));
	Core::GetHwndRef(_WindowIndex) = NULL;
	_Event->type = Event::Closed;
	_IsOpen = false;
}
void Window::clear(const Color& clr)
{
	_ClearerColor = clr.getColor();
	RECT _Rect = { 0, 0, _ClientRect.right, _ClientRect.bottom };
	HBRUSH _Brush = CreateSolidBrush(RGB(_ClearerColor.r, _ClearerColor.g, _ClearerColor.b));
	FillRect(Core::GetMemHdcRef(_WindowIndex), &_Rect, _Brush);
	DeleteObject(_Brush);
}
void Window::fpsLimiter(Uint16 fps)
{
	LARGE_INTEGER _EndFrame;
	QueryPerformanceCounter(&_EndFrame);
	Int64 millisecs = ((_EndFrame.QuadPart - _StTick.QuadPart) * 1000) / _Freq.QuadPart;
	if (millisecs < (1000 / (fps * 2))) {
		Core::Delay((1000 / Uint16(fps * 2)) - millisecs);
	}
}
Vector2i Window::getPosition() const
{
	return Vector2i(_WindowTransform.posX, _WindowTransform.posY);
}
Vector2i Window::getSize() const
{
	return Vector2i(_WindowTransform.sizeX, _WindowTransform.sizeY);
}
void Window::setPosition(Int32 x, Int32 y)
{
	MoveWindow(Core::GetHwndRef(_WindowIndex), x, y, _WindowTransform.sizeX, _WindowTransform.sizeY, FALSE);
	_WindowTransform.posX = x;
	_WindowTransform.posY = y;
}
void Window::setSize(Int32 x, Int32 y)
{
	MoveWindow(Core::GetHwndRef(_WindowIndex), _WindowTransform.posX, _WindowTransform.posY, x, y, FALSE);
	_WindowTransform.sizeX = x;
	_WindowTransform.sizeY = y;
	if (_Event)
		_Event->type = Event::Resized;
	GetClientRect(Core::GetHwndRef(_WindowIndex), &_ClientRect);
	if (_mWindowHDC_Bitmap != NULL) {
		SelectObject(Core::GetMemHdcRef(_WindowIndex), _Old_mWindowHDC_Bitmap);
		DeleteObject(_mWindowHDC_Bitmap);
		_mWindowHDC_Bitmap = NULL;
	}
	HDC _TempHDC = GetDC(Core::GetHwndRef(_WindowIndex));
	_mWindowHDC_Bitmap = CreateCompatibleBitmap(_TempHDC, _ClientRect.right + 10, _ClientRect.bottom + 10);
	ReleaseDC(Core::GetHwndRef(_WindowIndex), _TempHDC);
	SelectObject(Core::GetMemHdcRef(_WindowIndex), _mWindowHDC_Bitmap);
}
String Window::getTitle() const
{
	return _WindowTitle;
}
WL_NAMESPACE_END
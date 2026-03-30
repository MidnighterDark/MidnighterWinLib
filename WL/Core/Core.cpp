#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
HWND& Core::GetHwndRef()
{
	static HWND _Hwnd{ NULL };
	return _Hwnd;
}
HDC& Core::GetMemHdcRef()
{
	static HDC _Hdc{ NULL };
	return _Hdc;
}
WL_NAMESPACE_END
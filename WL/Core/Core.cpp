#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
HWND& Core::GetHwndRef(Uint16 i)
{
	static HWND _Hwnd[SHORTMAX]{ NULL };
	return _Hwnd[i];
}
HDC& Core::GetMemHdcRef(Uint16 i)
{
	static HDC _Hdc[SHORTMAX]{ NULL };
	return _Hdc[i];
}
Uint16& Core::GetWindowQuantity()
{
	static Uint16 _WindowQuantity = NULL;
	return _WindowQuantity;
}
void Core::Delay(Uint32 mils)
{
	LARGE_INTEGER _st, _tp;
	QueryPerformanceCounter(&_st);
	LARGE_INTEGER _Freq;
	QueryPerformanceFrequency(&_Freq);
	if (_Freq.QuadPart != 0) {
		Uint64 _rt = _st.QuadPart + (_Freq.QuadPart / 1000) * mils;
		while (true) {
			QueryPerformanceCounter(&_tp);
			if (_rt <= _tp.QuadPart)
				return;
		}
	}
}
WL_NAMESPACE_END
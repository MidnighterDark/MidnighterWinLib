#include <WL/Core/Core.hpp>
#include <iostream>
#include <WL/Core/Container.hpp>
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
void Core::Delay(Uint64 mils)
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
void Core::GetPCParametrs(pPCParametrs dest)
{
	dest->ScreenSizeX = GetSystemMetrics(SM_CXSCREEN);
	dest->ScreenSizeY = GetSystemMetrics(SM_CYSCREEN);
	wchar_t pcName[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };
	DWORD _PCN_Size = (MAX_COMPUTERNAME_LENGTH + 1);
	if (GetComputerNameW(pcName, &_PCN_Size)) {
		dest->PCName = new wchar_t[_PCN_Size];
		memcopy<wchar_t>(dest->PCName, pcName, _PCN_Size);
	}
	else {
		DWORD error = GetLastError();
		std::wcout << L"Ошибка получения имени компьютера: " << error << std::endl;
		return;
	}
}
WL_NAMESPACE_END
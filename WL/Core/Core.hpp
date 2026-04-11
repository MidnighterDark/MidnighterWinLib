//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#define NOMINMAX
#ifndef WINLIB_CORE_HPP_INIT
#define WINLIB_CORE_HPP_INIT
//Helpers
#define SHORTMIN  (-32767)
#define SHORTMAX  32767
#define USHORTMAX 0xFFFF
#define INTMIN    (-2147483647)
#define INTMAX    2147483647
#define UINTMAX   0xFFFFFFFF
#define PI 3.1415926535f
//WINLIB_STATIC, WINLIB_EXPORTS and init WINLIB_API
#ifdef WINLIB_STATIC
	#define WINLIB_API
#else
	#ifdef WINLIB_EXPORTS
		#pragma message("WINLIB: Building DLL (dllexport)")
		#define WINLIB_API __declspec(dllexport)
	#else
		#pragma message("WINLIB: Using DLL (dllimport)")
		#define WINLIB_API __declspec(dllimport)
	#endif
#endif
//
#define WL_NAMESPACE_BEGIN namespace wl {
#define WL_NAMESPACE_END }
#include <Windows.h>
WL_NAMESPACE_BEGIN
//Typedef for unsigned char.
typedef unsigned char      Uint8;
//Typedef for unsigned short.
typedef unsigned short     Uint16;
//Typedef for unsigned int.
typedef unsigned int       Uint32;
//Typedef for unsigned long long.
typedef unsigned long long Uint64;
//Typedef for signed char.
typedef signed char        Int8;
//Typedef for signed short.
typedef signed short	   Int16;
//Typedef for signed int.
typedef signed int         Int32;
//Typedef for signed long long.
typedef signed long long   Int64;
//Custom boolean type
typedef unsigned char      Bool;
class Core {
public:
	//Get the current HWND reference.
	static WINLIB_API HWND&   GetHwndRef(Uint16);
	//Get the current HDC reference.
	static WINLIB_API HDC&    GetMemHdcRef(Uint16);
	//Get current windows quantity
	static WINLIB_API Uint16& GetWindowQuantity();
	//Sleep for time
	static WINLIB_API void    Delay(Uint32 mils);
private:
	Core() = delete;
	~Core() = delete;
};
WL_NAMESPACE_END
//DELAY is macro for... thread delay!!!
#define DELAY(x) Core::Delay(x)
#endif //WINLIB_CORE_HPP_INIT
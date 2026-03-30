//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_CORE_HPP_INIT
#define WINLIB_CORE_HPP_INIT
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
	static HWND& GetHwndRef();
	//Get the current HDC reference.
	static HDC& GetMemHdcRef();
private:
	Core() = delete;
	~Core() = delete;
};
WL_NAMESPACE_END
#endif //WINLIB_CORE_HPP_INIT
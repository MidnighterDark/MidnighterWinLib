//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_STRING_HPP
#define WINLIB_STRING_HPP
#include <WL/Core/Core.hpp>
#include <string>
#include <Windows.h>
WL_NAMESPACE_BEGIN
class WINLIB_API String {
	std::wstring _Data;
public:
	String();
	String(LPCSTR str);
	String(LPCWSTR wideString);
	String(std::string str);
	String(std::wstring wstr);

	void operator=(const char* str);
	void operator=(const wchar_t* wstr);
	void operator+=(const char* str);
	void operator+=(const wchar_t* wstr);

	static std::wstring toWideString(const std::string& utf8_str);
	static std::string	toNarrowString(const std::wstring& wstr);

	std::wstring		getWideString() const;
	std::string			getNarrowString() const;
	LPCWSTR				getLpcwstr() const;

	operator const wchar_t* () const;
	operator const char* () const;
	operator std::wstring() const;
	operator std::string() const;
};
WL_NAMESPACE_END
#endif //WINLIB_STRING_HPP
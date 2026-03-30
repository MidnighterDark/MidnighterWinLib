//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_STRING_HPP
#define WINLIB_STRING_HPP
#include <WL/Core/Core.hpp>
#include <string>
#include <Windows.h>
WL_NAMESPACE_BEGIN
std::wstring _To_Wstring(const std::string& utf8_str);
std::string _To_String(const std::wstring& wstr);
class String {
	std::wstring _Data;
public:
	String();
	String(LPCSTR _Str);
	String(LPCWSTR _LpStr);

	void operator=(const char* _Str);
	void operator=(const wchar_t* _Str);
	void operator+=(const char* _Str);
	void operator+=(const wchar_t* _Str);

	static std::wstring toWideString(const std::string& utf8_str);
	static std::string toNarrowString(const std::wstring& wstr);

	std::wstring getWideString() const;
	std::string getNarrowString() const;
	LPCWSTR getLpcwstr() const;
private:
};
WL_NAMESPACE_END
#endif //WINLIB_STRING_HPP
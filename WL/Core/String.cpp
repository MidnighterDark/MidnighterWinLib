#include <WL/Core/String.hpp>
WL_NAMESPACE_BEGIN
std::wstring _To_Wstring(const std::string& utf8_str) {
    if (utf8_str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(),
        (int)utf8_str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(),
        (int)utf8_str.size(), &wstr[0], size_needed);
    return wstr;
}
std::string _To_String(const std::wstring& wstr) {
    if (wstr.empty()) return "";
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(),
        (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(),
        (int)wstr.size(), &str[0], size_needed, NULL, NULL);
    return str;
}
String::String()
{
	_Data[0] = '\0';
}
String::String(LPCSTR _Str)
{
    _Data = _To_Wstring(_Str);
}
String::String(LPCWSTR _LpStr)
{
    _Data = _LpStr;
}
void String::operator=(const char* _Str)
{
    _Data = _To_Wstring(std::string(_Str));
}
void String::operator=(const wchar_t* _Wstr)
{
    _Data = _Wstr;
}
void String::operator+=(const char* _Str)
{
    _Data += _To_Wstring(std::string(_Str));
}
void String::operator+=(const wchar_t* _Str)
{
    _Data += _Str;
}
std::wstring String::toWideString(const std::string& utf8_str)
{
    return _To_Wstring(utf8_str);
}
std::string String::toNarrowString(const std::wstring& wstr)
{
    return _To_String(wstr);
}
std::wstring String::getWideString() const
{
    return std::wstring(_Data);
}
std::string String::getNarrowString() const
{
    return std::string(_To_String(_Data));
}

LPCWSTR String::getLpcwstr() const
{
    return _Data.c_str();
}
WL_NAMESPACE_END
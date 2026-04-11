#include <WL/Window/Font.hpp>
#include <fstream>
#include <iostream>
WL_NAMESPACE_BEGIN
#pragma pack(push, 1)
struct TTFHeader {
    Uint32 sfntVersion;
    Uint16 numTables;
    Uint16 searchRange;
    Uint16 entrySelector;
    Uint16 rangeShift;
};
struct TableRecord {
    char tag[4];
    Uint32 checkSum;
    Uint32 offset;
    Uint32 length;
};
struct NameTableHeader {
    Uint16 format;
    Uint16 count;
    Uint16 stringOffset;
};
struct NameRecord {
    Uint16 platformID;
    Uint16 encodingID;
    Uint16 languageID;
    Uint16 nameID;
    Uint16 length;
    Uint16 offset;
};
#pragma pack(pop)
Uint32 bigToLittle32Endian(Uint32 n) {
    return ((n & 0x000000FF) << 24) |
        ((n & 0x0000FF00) << 8) |
        ((n & 0x00FF0000) >> 8) |
        ((n & 0xFF000000) >> 24);
}
Uint16 bigToLittleEndian(Uint16 n) {
    return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
}
Font::Font(String fontFamalyName)
{
    _FontFamalyName = fontFamalyName;
}
Font::~Font()
{
    RemoveFontResourceEx(_Path.getLpcwstr(), FR_PRIVATE, NULL);
}
bool Font::loadFromFile(String path)
{
    _Path = path;
    _FontFamalyName = L"";
    AddFontResourceEx(path.getLpcwstr(), FR_PRIVATE, NULL);
    using namespace std;
    ifstream _TTF(path.getNarrowString(), ios::binary);
    if (!_TTF.is_open()) {
        std::cout << "ERROR: File \"" + path.getNarrowString() + "\" can't open.\n";
        return false;
    }
    TTFHeader _TTFHeader;
    _TTF.read(reinterpret_cast<char*>(&_TTFHeader), sizeof(_TTFHeader));
    for (Uint16 i = 0; i < bigToLittleEndian(_TTFHeader.numTables); i++) {
        TableRecord tableRecord;
        _TTF.read(reinterpret_cast<char*>(&tableRecord), sizeof(tableRecord));
        Uint32 offset = bigToLittle32Endian(tableRecord.offset);
        if (tableRecord.tag[0] == 'n' && tableRecord.tag[1] == 'a' && tableRecord.tag[2] == 'm' && tableRecord.tag[3] == 'e') {
            _TTF.seekg(offset);
            NameTableHeader nameTableHeader;
            _TTF.read(reinterpret_cast<char*>(&nameTableHeader), sizeof(nameTableHeader));
            for (Uint16 ni = 0; ni < bigToLittleEndian(nameTableHeader.count); ni++) {
                NameRecord nameRecord;
                _TTF.read(reinterpret_cast<char*>(&nameRecord), sizeof(nameRecord));
                if (bigToLittleEndian(nameRecord.platformID) == 0 || bigToLittleEndian(nameRecord.platformID) == 3) {
                    if (bigToLittleEndian(nameRecord.nameID) == 1) {
                        _TTF.seekg(bigToLittle32Endian(tableRecord.offset) + bigToLittleEndian(nameTableHeader.stringOffset) + bigToLittleEndian(nameRecord.offset));
                        for (Uint16 nni = 0; nni < (bigToLittleEndian(nameRecord.length) / 2); nni++) {
                            char _lowByte, _highByte;
                            _TTF.read(&_highByte, 1);
                            _TTF.read(&_lowByte, 1);
                            wchar_t _re =  wchar_t(static_cast<wchar_t>(_lowByte) | (static_cast<wchar_t>(_highByte) << 8));
                            wchar_t _rearr[2] = { _re, '\0' };
                            _FontFamalyName += _rearr;
                        }
                        _TTF.close();
                        return true;
                    }
                }
            }
        }
    }
    _TTF.close();
    return false;
}
String Font::getFontFamalyName() const
{
    return _FontFamalyName;
}
const Font Font::DefaultOS = Font();
WL_NAMESPACE_END
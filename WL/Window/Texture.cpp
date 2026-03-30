#include <WL/Window/Texture.hpp>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
WL_NAMESPACE_BEGIN
#pragma pack(push, 1)
struct BitmapFileHeader {
    Uint16 type;
    Uint32 size;
    Uint16 reserved1;
    Uint16 reserved2;
    Uint32 dataOffset;
};

struct BitmapInfoHeader {
    Uint32 size;
    Int32  width;
    Int32  height;
    Uint16 planes;
    Uint16 bitCount;
    Uint32 compression;
    Uint32 imageSize;
    Int32  xPelsPerMeter;
    Int32  yPelsPerMeter;
    Uint32 colorsUsed;
    Uint32 colorsImportant;
};
#pragma pack(pop)
void Texture::create(const Color& color, Uint16 width, Uint16 height)
{
	_Width = width;
	_Height = height;
	for (Uint32 _I = 0; _I < _Width * _Height; _I++) {
		_Pixels.add(color.getData());
	}
}
void Texture::loadFromTDF(String _Path)
{
	using namespace std;
	ifstream _DTF(_Path.getNarrowString(), ios::binary);
    if (!_DTF.is_open()) {
        std::cout << "ERROR: File: \"" + _Path.getNarrowString() + "\" can't open.\n";
        this->create(Color(255, 0, 0), 100, 100);
        return;
    }
	_DTF.read(reinterpret_cast<char*>(&_Width), sizeof(Uint16));
	_DTF.read(reinterpret_cast<char*>(&_Height), sizeof(Uint16));
    Uint32* pPixels = new Uint32[_Width * _Height];
	_DTF.read(reinterpret_cast<char*>(pPixels), sizeof(Uint32) * _Width * _Height);
    for (Uint32 i = 0; i < (_Width * _Height); i++) {
        pPixels[i] = pPixels[i] | (Uint32(0xFF) << 24);
    }
    _Pixels.replaceData(pPixels, _Width * _Height);
	_DTF.close();
    delete[] pPixels;
}
void Texture::loadFromBMP(String _Path)
{
    using namespace std;
    ifstream _BMP(_Path.getNarrowString(), ios::binary);
    if (!_BMP.is_open()) {
        std::cout << "ERROR: File: \"" + _Path.getNarrowString() + "\" can't open.\n";
        this->create(Color(255, 0, 0), 100, 100);
        return;
    }
    BitmapFileHeader _BMPHeader;
    BitmapInfoHeader _BMPIHeader;
    _BMP.read(reinterpret_cast<char*>(&_BMPHeader), sizeof(_BMPHeader));
    _BMP.read(reinterpret_cast<char*>(&_BMPIHeader), sizeof(_BMPIHeader));
    _Width = _BMPIHeader.width;
    _Height = abs(_BMPIHeader.height);
    Uint32* pPixels = new Uint32[_Width * _Height + 1];
    int padding = (4 - (_Width * 3) % 4) % 4;
    for (Uint32 y = 0; y < _Height; y++) {
        for (Uint32 x = 0; x < _Width; x++) {
            Uint8 pixelData[3];
            _BMP.read(reinterpret_cast<char*>(pixelData), 3);
            pPixels[y * _Width + x] =
                (static_cast<Uint32>(Uint8(0xFF)) << 24) |
                (static_cast<Uint32>(pixelData[2]) << 16) |
                (static_cast<Uint32>(pixelData[1]) << 8) |
                static_cast<Uint32>(pixelData[0]);
        }
        if (padding > 0) {
            _BMP.ignore(padding);
        }
    }
    _Pixels.replaceData(pPixels, (_Width * _Height));
    _BMP.close();
    delete[] pPixels;
}
void Texture::loadFromPNG(String _Path)
{
    int channels;
    Uint8* pixels = stbi_load(_Path.getNarrowString().c_str(), reinterpret_cast<int*>(&_Width), reinterpret_cast<int*>(&_Height), &channels, 4);
    if (!pixels) {
        std::cout << "ERROR: File: \"" + _Path.getNarrowString() + "\" can't open.\n";
        this->create(Color(255, 0, 0), 100, 100);
        return;
    }
    Uint32* _Temp_Pixels = new Uint32[_Width * _Height];
    for (Uint32 y = 0; y < _Height; y++) {
        for (Uint32 x = 0; x < _Width; x++) {
            Uint32 srcY = _Height - 1 - y;
            Uint32 srcIdx = (srcY * _Width + x) * 4;
            Uint32 dstIdx = y * _Width + x;

            _Temp_Pixels[dstIdx] =
                (static_cast<Uint32>(pixels[srcIdx + 3]) << 24) |
                (static_cast<Uint32>(pixels[srcIdx + 0]) << 16) |
                (static_cast<Uint32>(pixels[srcIdx + 1]) << 8) |
                (static_cast<Uint32>(pixels[srcIdx + 2]));
        }
    }
    _Pixels.replaceData(_Temp_Pixels, (_Width * _Height));
    delete[] _Temp_Pixels;
    stbi_image_free(pixels);
}
void Texture::operator=(const Texture& val)
{
    _Pixels.replaceData(val._Pixels.data(), val._Pixels.size());
    _Width = val._Width;
    _Height = val._Height;
}
bool Texture::operator==(const Texture& verifable) const
{
    if (_Pixels.data() == verifable._Pixels.data() && _Width == verifable._Width && _Height == verifable._Height) {
        return true;
    }
    return false;
}
bool Texture::operator!=(const Texture& verifable) const
{
    if (_Pixels.data() == verifable._Pixels.data() && _Width == verifable._Width && _Height == verifable._Height) {
        return false;
    }
    return true;
}
WL_NAMESPACE_END
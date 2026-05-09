//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_CONTAINER_HPP
#define WINLIB_CONTAINER_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Ptr.hpp>
#include <iostream>
WL_NAMESPACE_BEGIN
//Copy memory from _Dest to _Src
//_Quat is a size of copying data
//_Begin_Pos is a begined index of _Dest data
template<typename T>
void memcopy(T* _Dest, T* _Src, Uint32 _Quat, Uint32 _Begin_Pos = 0)
{
	for (Uint32 i = 0; i < (_Quat - _Begin_Pos); i++) {
		_Dest[i + _Begin_Pos] = _Src[i];
	}
}
//This object like std::vector
template<typename T>
class container {
	T* _Data = nullptr;
	Uint32 _Capacity = 2;
	Uint32 _Size = 0;
	T* __Resize__() {
		if (_Size >= _Capacity || _Size == 0) {
			_Capacity *= 2;
			_Data = static_cast<T*>(operator new[](_Capacity * sizeof(T)));
		}
		return _Data;
	}
public:
	//destructor
	~container(void) {
		if (_Data != nullptr)
			delete[] _Data;
	}
	//For clear all in container
	void clear(void) {
		delete[] _Data;
		_Data = nullptr;
		_Capacity = 2;
		_Size = 0;
	}
	//Checks if the container is empty
	bool isEmpty() {
		return bool(_Size == 0);
	}
	//This function for adding something in container
	void add(T _Val) {
		T* _Temp = _Data;
		_Data = __Resize__();
		if (_Temp != _Data) {
			memcopy<T>(_Data, _Temp, _Size);
			delete[] _Temp;
		}
		_Data[_Size] = _Val;
		_Size++;
	}
	//Adds _Val to the beginning of the array
	void addBack(T _Val) {
		T* _Temp = _Data;
		_Size++;
		_Data = __Resize__();
		_Data[0] = _Val;
		if (_Temp != _Data) {
			memcopy<T>(_Data, _Temp, _Size, 1);
			delete[] _Temp;
		}
	}
	//For remove something by index
	void remove(Uint32 _Pos) {
		for (Uint32 i = 0; i < _Size; i++) {
			if (i >= _Pos) {
				_Data[i] = _Data[i + 1];
			}
			else {
				_Data[i] = _Data[i];
			}
		}
		_Size--;
	}
	//This function allocates heap memory for the container
	//May optimizate "add" and "addBack" function
	void alloc(Uint32 _NewSize) {
		if (_Data != nullptr)
			delete[] _Data;
		_Data = static_cast<T*>(operator new[](_NewSize * sizeof(T)));
		_Capacity = _NewSize;
		_Size = 0;
	}
	//Replacing the current data on the new
	void replaceData(T* _NewData, Uint32 _NewSize) {
		alloc(_NewSize);
		_Size = _NewSize;
		memcopy<T>(_Data, _NewData, _NewSize);
	}
	//This operator works like "get" on anything
	T& operator[](Uint32 _Pos) {
		return _Data[_Pos];
	}
	//Returns a pointer to the beginning of the data in the container.
	T* data(void) const { return _Data; }
	Uint32 capacity(void) const { return _Capacity; }
	Uint32 size(void) const { return _Size; }
	Uint64 currentbytesize(void) const { return (_Size * sizeof(T)); }
	T* begin() { return _Data; }
	T* end() { return (_Data + _Size); }
};
/*more*/
/*some defines*/
#define vec			container
#define vector		container
#define Container	container
/*end of WinLib namespace*/
WL_NAMESPACE_END
#endif //WINLIB_CONTAINER_HPP
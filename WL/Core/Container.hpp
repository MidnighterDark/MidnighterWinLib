//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_CONTAINER_HPP
#define WINLIB_CONTAINER_HPP
#include <WL/Core/Core.hpp>
#include <iostream>
WL_NAMESPACE_BEGIN
//Copy memory from _Dest to _Src
template<typename T>
void memcopy(T* _Dest, T* _Src, Uint32 _Quat)
{
	for (Uint32 i = 0; i < _Quat; i++) {
		_Dest[i] = _Src[i];
	}
}
//This object like std::vector
template<typename T>
class container {
	T* _Data = nullptr;
	Uint32 _Capacity = 2;
	Uint32 _Size = 0;
	T* _Resize() {
		if (_Size >= _Capacity || _Size == 0) {
			_Capacity *= 2;
			_Data = static_cast<T*>(operator new[](_Capacity * sizeof(T)));
		}
		return _Data;
	}
public:
	//destructor
	~container() {
		if (_Data != nullptr)
			delete[] _Data;
	}
	//This function for adding something in container
	void add(T _Val) {
		T* _Temp = _Data;
		_Data = _Resize();
		if (_Temp != _Data) {
			memcopy<T>(_Data, _Temp, _Size);
			delete[] _Temp;
		}
		_Data[_Size] = _Val;
		_Size++;
	}
	//This function allocates heap memory for the container
	//May optimizate "add" function
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
	T* data() const { return _Data; }
	Uint32 capacity() const { return _Capacity; }
	Uint32 size() const { return _Size; }
	Uint64 currentbitsize() const { return (_Size * sizeof(T)); }
};
/*more*/
/*some defines*/
#define vec			container
#define vector		container
#define Container	container
WL_NAMESPACE_END
#endif //WINLIB_CONTAINER_HPP
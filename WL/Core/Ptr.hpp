#ifndef WINLIB_PTR_HPP
#define WINLIB_PTR_HPP
#include <WL/Core/Core.hpp>
WL_NAMESPACE_BEGIN
//This toy is for playing
template<typename T>
class _RefCounter {
	T _Refs = 0;
public:
	void _AddRef() {
		_Refs += 1;
	}
	void _SubRefs() {
		if (_Refs > 0) _Refs -= 1;
	}
	operator T() {
		return _Refs;
	}
};
/*This class is a pathetic imitation of realy SharedPtr!!!*/
template<typename T>
class Pathetic_SharedPtr {
	T* _Ptr = nullptr;
	_RefCounter<Uint32> _Refs;
public:
	Pathetic_SharedPtr(T* _NewPtr) {
		if (!bool(_Refs)) _Refs._AddRef();
		if (_Ptr) free(static_cast<void*>(_Ptr));
		_Ptr = _NewPtr;
	}
	Pathetic_SharedPtr(Pathetic_SharedPtr<T>& _Other) {
		if (!bool(_Refs)) _Refs._AddRef();
		_Other._Refs._AddRef();
		if (_Ptr) free(static_cast<void*>(_Ptr));
		_Ptr = _Other._Ptr;
	}
	~Pathetic_SharedPtr() {
		_Refs._SubRefs();
		if (_Ptr && _Refs == 0) free(static_cast<void*>(_Ptr));
	}
	void operator=(T* _NewPtr) {
		if (!bool(_Refs)) _Refs._AddRef();
		if (_Ptr) free(static_cast<void*>(_Ptr));
		_Ptr = _NewPtr;
	}
	void operator=(Pathetic_SharedPtr<T>& _Other) {
		if (!bool(_Refs)) _Refs._AddRef();
		_Other._Refs._AddRef();
		if (_Ptr) free(static_cast<void*>(_Ptr));
		_Ptr = _Other._Ptr;
	}
	operator T* () {
		_Refs._AddRef();
		return _Ptr;
	}
};
WL_NAMESPACE_END
#endif // WINLIB_PTR_HPP
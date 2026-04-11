//Copyright Midnighter & MidnighterDark & ONION & ONION-Studio.
//If you are not working with the source code, PLEASE DO NOT MODIFY THIS FILE.
#ifndef WINLIB_EVENT_HPP
#define WINLIB_EVENT_HPP
#include <WL/Core/Core.hpp>
#include <WL/Core/Vector.hpp>
WL_NAMESPACE_BEGIN
namespace Mouse {
	Vector2i getGlobalMousePos();
}
class Key {
public:
	enum Type {
		KeyA = 65,
		KeyB = 66,
		KeyC = 67,
		KeyD = 68,
		KeyE = 69,
		KeyF = 70,
		KeyG = 71,
		KeyH = 72,
		KeyI = 73,
		KeyJ = 74,
		KeyK = 75,
		KeyL = 76,
		KeyM = 77,
		KeyN = 78,
		KeyO = 79,
		KeyP = 80,
		KeyQ = 81,
		KeyR = 82,
		KeyS = 83,
		KeyT = 84,
		KeyU = 85,
		KeyV = 86,
		KeyW = 87,
		KeyX = 88,
		KeyY = 89,
		KeyZ = 90,
		KeyEscape = 27,
		KeyTab = 9,
		KeyCapsLock = 20,
		KeyShift = 16,
		KeyCtrl = 17,
		KeySpace = 32,
		KeyUp = 38,
		KeyDown = 40,
		KeyLeft = 37,
		KeyRight = 39,
		KeyInsert = 45,
		KeyDelete = 46,
		KeyEnd = 35,
		KeyHome = 36,
		KeyPageUp = 33,
		KeyPageDown = 34,
		KeyF1 = 112,
		KeyF2 = 113,
		KeyF3 = 114,
		KeyF4 = 115,
		KeyF5 = 116,
		KeyF6 = 117,
		KeyF7 = 118,
		KeyF8 = 119,
		KeyF9 = 120,
		KeyF11 = 122,
	};
};
class WINLIB_API Event {
public:
	enum _Ty {
		Closed,
		Resized,
		None,
	};
	_Ty type;
	bool isPressed(Key::Type key) const;
};
WL_NAMESPACE_END
#endif //WINLIB_EVENT_HPP
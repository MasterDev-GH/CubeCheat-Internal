#pragma once

class Hook {
	BYTE* hookPosition { nullptr };
	int hookLength { -1 };
	BYTE stolenBytes[30] { 0 };
	bool isHookActive { false };

	// For trampoline hooks
	BYTE* functionToCall { nullptr };
	DWORD hookToTrampJump;
	DWORD trampToFunctionCall;
	DWORD functionReturnJump;

	BYTE* trampoline { nullptr };

	BYTE preserveStack[2] { 0x60, 0x9C }; // pushad, pushfd
	BYTE releaseStack[2] { 0x9D, 0x61 }; // popad, popfd
	bool isTrampAlreadyBuilt { false };
public:
	// stolen bytes before the func call
	void toggleTrampSBF();
	// stolen bytes last (after func call)
	void toggleTrampSBL();

	Hook(BYTE* hookPosition, BYTE* functionToCall, int hookLength);
	Hook();
};
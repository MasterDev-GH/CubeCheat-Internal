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

	// For detour hooks
	DWORD hookToDetourJump;
public:
	// also for detour hooks
	DWORD detourReturnJump;
public:
	// stolen bytes before the func call
	void toggleTrampSBF();
	// stolen bytes last (after func call)
	void toggleTrampSBL();
	// for detours
	void toggleDetour();
	// get status of whether hook is active or not
	bool isHookOn();

	Hook(BYTE* hookPosition, BYTE* functionToCall, int hookLength);
	Hook();
};

class Nop {
	BYTE* nopPosition { nullptr };
	int  nopLength { -1 };
	BYTE nopedBytes[30] { 0 };
	bool isNopActive { false };
public:
	// toggle the nop on or off
	void toggleNop();
	// get the status of whether nop is on or off
	bool isNopOn();

	Nop(BYTE* nopPosition, int nopLength);
	Nop();
};


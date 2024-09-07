#include "pch.h"
#include "Memory.h"

void Hook::toggleTrampSBF() {
	isHookActive = !isHookActive;

	DWORD oldProtection;
	VirtualProtect(hookPosition, hookLength, PAGE_EXECUTE_READWRITE, &oldProtection);

	if (isHookActive) {
		if (!isTrampAlreadyBuilt) {
			// stolen bytes first
			memcpy(trampoline, stolenBytes, hookLength);
			// preserve stack
			memcpy(trampoline + hookLength, preserveStack, sizeof(preserveStack));
			// call your function
			*(trampoline + hookLength + sizeof(preserveStack)) = 0xE8;
			*reinterpret_cast<DWORD*>((trampoline + hookLength + sizeof(preserveStack) + 1)) = trampToFunctionCall;
			// release stack
			memcpy(trampoline + hookLength + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack));
			// jump back
			*(trampoline + hookLength + sizeof(preserveStack) + 5 + sizeof(releaseStack)) = 0xE9;
			*reinterpret_cast<DWORD*>((trampoline + hookLength + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 1)) = functionReturnJump;
			// Trampoline is now build, no need to build it again.
			isTrampAlreadyBuilt = true;
		}

		memset(hookPosition, 0x90, hookLength);
		*hookPosition = 0xE9;
		*reinterpret_cast<DWORD*>((hookPosition + 1)) = hookToTrampJump;
	} else {
		memcpy(hookPosition, stolenBytes, hookLength);
	}

	VirtualProtect(hookPosition, hookLength, oldProtection, &oldProtection);
}

Hook::Hook(BYTE* hookPosition, BYTE* functionToCall, int hookLength) {
	this->hookPosition = hookPosition;
	this->functionToCall = functionToCall;
	this->hookLength = hookLength;

	memcpy(stolenBytes, hookPosition, hookLength);

	trampoline = (BYTE*)VirtualAlloc(nullptr, 30, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	hookToTrampJump = static_cast<DWORD>(trampoline - (hookPosition + 5));
	trampToFunctionCall = static_cast<DWORD>(functionToCall - (trampoline + hookLength + sizeof(preserveStack) + 5));
	functionReturnJump = static_cast<DWORD>((hookPosition + hookLength) - (trampoline + hookLength + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 5));
}

Hook::Hook() {

}
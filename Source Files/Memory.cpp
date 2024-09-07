#include "pch.h"
#include "Memory.h"

void Hook::toggleTrampSBF() {
	isHookActive = !isHookActive;

	DWORD oldProtection; 
	VirtualProtect(hookPosition, hookLength, PAGE_EXECUTE_READWRITE, &oldProtection);

	if (isHookActive) {
		if (!isTrampAlreadyBuilt) {
			// Calculate the jump from our function to Assault Cube frame loop
			trampToFunctionCall = static_cast<DWORD>(functionToCall - (trampoline + hookLength + sizeof(preserveStack) + 5));
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

void Hook::toggleTrampSBL() {
	isHookActive = !isHookActive;

	DWORD oldProtection;
	VirtualProtect(hookPosition, hookLength, PAGE_EXECUTE_READWRITE, &oldProtection);

	if (isHookActive) {
		if (!isTrampAlreadyBuilt) {
			// Calculate the jump from our function to Assault Cube frame loop
			trampToFunctionCall = static_cast<DWORD>(functionToCall - (trampoline + sizeof(preserveStack) + 5));
			// preserve stack
			memcpy(trampoline, preserveStack, sizeof(preserveStack));
			// call your function
			*(trampoline + sizeof(preserveStack)) = 0xE8;
			*reinterpret_cast<DWORD*>((trampoline + sizeof(preserveStack) + 1)) = trampToFunctionCall;
			// release stack
			memcpy(trampoline + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack));
			// stolen bytes last
			memcpy(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack), stolenBytes, hookLength);
			// jump back
			*(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack) + hookLength) = 0xE9;
			*reinterpret_cast<DWORD*>((trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack) + hookLength + 1)) = functionReturnJump;
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

bool Hook::isHookOn() {
	return isHookActive;
}

Hook::Hook(BYTE* hookPosition, BYTE* functionToCall, int hookLength) {
	this->hookPosition = hookPosition;
	this->functionToCall = functionToCall;
	this->hookLength = hookLength;

	memcpy(stolenBytes, hookPosition, hookLength);

	// trampoline jumps
	trampoline = (BYTE*)VirtualAlloc(nullptr, 30, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	hookToTrampJump = static_cast<DWORD>(trampoline - (hookPosition + 5));
	functionReturnJump = static_cast<DWORD>((hookPosition + hookLength) - (trampoline + hookLength + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 5));

	// detour jumps
	hookToDetourJump = static_cast<DWORD>(functionToCall - (hookPosition + 5));
	detourReturnJump = reinterpret_cast<DWORD>(hookPosition + hookLength);
}

void Hook::toggleDetour() {
	isHookActive = !isHookActive;

	DWORD oldProtection;
	VirtualProtect(hookPosition, hookLength, PAGE_EXECUTE_READWRITE, &oldProtection);

	if (isHookActive) {
		memset(hookPosition, 0x90, hookLength);
		*hookPosition = 0xE9;
		*reinterpret_cast<DWORD*>(hookPosition + 1) = hookToDetourJump;
	} else {
		memcpy(hookPosition, stolenBytes, hookLength);
	}

	VirtualProtect(hookPosition, hookLength, oldProtection, &oldProtection);
}

Hook::Hook() {

}

bool Nop::isNopOn() {
	return isNopActive;
}

void Nop::toggleNop() {
	isNopActive = !isNopActive;

	DWORD oldProtection;
	VirtualProtect(nopPosition, nopLength, PAGE_EXECUTE_READWRITE, &oldProtection); 

	if (isNopActive) {
		memset(nopPosition, 0x90, nopLength);
	} else {
		memcpy(nopPosition, nopedBytes, nopLength);
	}

	VirtualProtect(nopPosition, nopLength, oldProtection, &oldProtection);
}

Nop::Nop(BYTE* nopPosition, int nopLength) {
	this->nopPosition = nopPosition;
	this->nopLength = nopLength;

	memcpy(nopedBytes, nopPosition, nopLength);
}

Nop::Nop() {

}
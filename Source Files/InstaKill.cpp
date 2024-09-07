#include "pch.h"
#include "InstaKill.h"
#include "setupHooks.h"

void __declspec(naked) InstaKill() {
	__asm {
		subss xmm1, xmm0
		cvttss2si ecx, xmm1
		cmp dword ptr ds:[ebx + 0x224], 0
		jne skipHealthChange
		mov dword ptr ds:[ebx + 4], 0
		skipHealthChange:
		jmp InstaKillDetour.detourReturnJump
	}
}
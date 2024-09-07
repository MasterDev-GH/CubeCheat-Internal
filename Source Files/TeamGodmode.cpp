#include "pch.h"
#include "TeamGodmode.h"
#include "setupHooks.h"

void __declspec(naked) TeamGodmode() {
	__asm {
		cmp dword ptr ds:[ebx + 0x224], 1
		je skipDamage
		sub [ebx + 04], esi
		skipDamage:
		mov eax, esi
		jmp TeamGodmodeDetour.detourReturnJump
	}
}
#include "pch.h"
#include "HackFuncDeclarations.h"
#include "Globals.h"
#include "GameClasses.h"

static Ent *localPlayer = (Ent*)(*(pStartOfEntityList - 1));
static int myTeamNum = localPlayer->TeamNum;

void __declspec(naked) TeamGodmode() {
	__asm {
		push eax
		mov eax, myTeamNum
		cmp dword ptr ds:[ebx + 0x224], eax
		pop eax
		je skipDamage
		sub [ebx + 04], esi
		skipDamage:
		mov eax, esi
		jmp TeamGodmodeDetour.detourReturnJump
	}
}
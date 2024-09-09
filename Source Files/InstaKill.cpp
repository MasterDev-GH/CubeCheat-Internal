#include "pch.h"
#include "HackFuncDeclarations.h"
#include "Globals.h"
#include "GameClasses.h"

static Ent *localPlayer = (Ent*)(*(pStartOfEntityList - 1));
static int myTeamNum = localPlayer->TeamNum;

void __declspec(naked) InstaKill() {
	__asm {
		subss xmm1, xmm0
		cvttss2si ecx, xmm1
		push ecx
		mov ecx, myTeamNum
		cmp dword ptr ds:[ebx + 0x224], ecx
		pop ecx
		je skipHealthChange
		mov dword ptr ds:[ebx + 4], 0
		skipHealthChange:
		jmp InstaKillDetour.detourReturnJump
	}
}
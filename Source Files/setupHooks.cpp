#include "pch.h"
#include "setupHooks.h"
#include "Memory.h"
#include "MainHackLoop.h"
#include "TeamGodmode.h"
#include "InstaKill.h"

Hook mainHackLoopTramp;
Nop infAmmoNop;
Hook TeamGodmodeDetour;
Hook InstaKillDetour;

void setupHooks() {
	BYTE* moduleBaseAssaultCube = reinterpret_cast<BYTE*>(GetModuleHandle(L"ac_client.exe"));
	BYTE* moduleBaseOpenGl = reinterpret_cast<BYTE*>(GetModuleHandle(L"opengl32.dll"));

	Hook mainHackLoopTrampTemp(moduleBaseOpenGl + 0x4841E, reinterpret_cast<BYTE*>(mainHackLoop), 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	Nop infAmmoNopTemp(moduleBaseAssaultCube + 0xC73EF, 2);
	infAmmoNop = infAmmoNopTemp;

	Hook TeamGodmodeDetourTemp(moduleBaseAssaultCube + 0x1C223, reinterpret_cast<BYTE*>(TeamGodmode), 5);
	TeamGodmodeDetour = TeamGodmodeDetourTemp;

	Hook InstaKillDetourTemp(moduleBaseAssaultCube + 0x1C219, reinterpret_cast<BYTE*>(InstaKill), 8);
	InstaKillDetour = InstaKillDetourTemp;
}
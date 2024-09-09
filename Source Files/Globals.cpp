#include "pch.h"
#include "Globals.h"
#include "Memory.h"
#include "HackFuncDeclarations.h"



// Game Modules
BYTE* moduleBaseAssaultCube = reinterpret_cast<BYTE*>(GetModuleHandle(L"ac_client.exe"));
BYTE* moduleBaseOpenGl = reinterpret_cast<BYTE*>(GetModuleHandle(L"opengl32.dll"));

// Hooks/Nops
Hook mainHackLoopTramp(moduleBaseOpenGl + 0x4841E, reinterpret_cast<BYTE*>(mainHackLoop), 5);
Nop infAmmoNop(moduleBaseAssaultCube + 0xC73EF, 2);
Hook TeamGodmodeDetour(moduleBaseAssaultCube + 0x1C223, reinterpret_cast<BYTE*>(TeamGodmode), 5);
Hook InstaKillDetour(moduleBaseAssaultCube + 0x1C219, reinterpret_cast<BYTE*>(InstaKill), 8);

// Other variables
bool isHackOver = false;

// Game memory
int currentPlayerCount = *reinterpret_cast<int*>(moduleBaseAssaultCube + 0x18AC0C);
uintptr_t* pLocalPlayer = (uintptr_t*)(moduleBaseAssaultCube + 0x18AC00);
uintptr_t* pStartOfEntityList = (uintptr_t*)(moduleBaseAssaultCube + 0x18AC04);
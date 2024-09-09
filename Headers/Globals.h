#pragma once
#include "Memory.h"

// Game Modules
extern BYTE* moduleBaseAssaultCube;
extern BYTE* moduleBaseOpenGll;

// Hooks/Nops
extern Hook mainHackLoopTramp;
extern Nop infAmmoNop;
extern Hook TeamGodmodeDetour;
extern Hook InstaKillDetour;

// other variables
extern bool isHackOver;
extern int currentPlayerCount;

// pointers to game structs
extern uintptr_t* pLocalPlayer;
extern uintptr_t* pStartOfEntityList;
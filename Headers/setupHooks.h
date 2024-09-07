#pragma once
#include "Memory.h"

extern Hook mainHackLoopTramp;
extern Nop infAmmoNop;
extern Hook TeamGodmodeDetour;
extern Hook InstaKillDetour;

void setupHooks();
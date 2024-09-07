#include "pch.h"
#include "setupHooks.h"
#include "Memory.h"
#include "MainHackLoop.h"

Hook mainHackLoopTramp;

void setupHooks() {
	BYTE* moduleBaseOpenGl = reinterpret_cast<BYTE*>(GetModuleHandle(L"opengl32.dll"));

	Hook mainHackLoopTrampTemp(moduleBaseOpenGl + 0x4841E, reinterpret_cast<BYTE*>(mainHackLoop), 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;
}
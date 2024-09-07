#pragma once
#include "pch.h"
#include "MainHackLoop.h"
#include "setupHooks.h"

bool isHackOver = false;

void mainHackLoop() {
	static int x = 0;
	std::cout << x++ << '\n';

	if (GetAsyncKeyState(VK_F1) & 1) {
		infAmmoNop.toggleNop();
	}

	if (GetAsyncKeyState(VK_F2) & 1) {
		TeamGodmodeDetour.toggleDetour();
	}

	if (GetAsyncKeyState(VK_F3) & 1) {
		InstaKillDetour.toggleDetour();
	}

	if (GetAsyncKeyState(VK_F10) & 1) {
		mainHackLoopTramp.toggleTrampSBL();
		isHackOver = true;
	}
} 
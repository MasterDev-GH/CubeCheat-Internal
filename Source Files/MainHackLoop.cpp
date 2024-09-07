#pragma once
#include "pch.h"
#include "MainHackLoop.h"
#include "setupHooks.h"

bool isHackOver = false;

void mainHackLoop() {
	static int x = 0;
	std::cout << x++ << '\n';

	if (GetAsyncKeyState(VK_F12) & 1) {
		mainHackLoopTramp.toggleTrampSBL();
		isHackOver = true;
	}
}
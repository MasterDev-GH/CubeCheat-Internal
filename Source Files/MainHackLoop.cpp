#pragma once
#include "pch.h"
#include "HackFuncDeclarations.h"
#include "ConsoleAndInput.h"
#include "Globals.h"

void mainHackLoop() {
	handleInput();

	int playerCountCheck = *reinterpret_cast<int*>(moduleBaseAssaultCube + 0x18AC0C);

	if (playerCountCheck != currentPlayerCount) {
		currentPlayerCount = playerCountCheck;
	}
} 
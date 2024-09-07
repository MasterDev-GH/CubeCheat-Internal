#pragma once
#include "pch.h"
#include "MainHackLoop.h"
#include "setupHooks.h"
#include "ConsoleAndInput.h"

bool isHackOver = false;

void mainHackLoop() {
	handleInput();
} 
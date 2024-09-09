#include "pch.h"
#include "ConsoleAndInput.h"
#include "Globals.h"
#include "HackFuncDeclarations.h"
#include "Aimbot.h"

// Updates the console
void printUI() {
	system("cls");
	std::cout << "========================================\n";
	std::cout << std::format("{:<20}", "Infinite Ammo") << "[F1]" << "----------[" << (infAmmoNop.isNopOn() ? "ON" : "OFF") << "]\n";
	std::cout << std::format("{:<20}", "Team Godmode") << "[F2]" << "----------[" << (TeamGodmodeDetour.isHookOn() ? "ON" : "OFF") << "]\n";
	std::cout << std::format("{:<20}", "InstaKill") << "[F3]" << "----------[" << (InstaKillDetour.isHookOn() ? "ON" : "OFF") << "]\n";
	std::cout << std::format("{:<20}", "Show/Hide Console") << "[F9]\n";
	std::cout << std::format("{:<20}", "Uninject Dll") << "[F10]\n";
	std::cout << std::format("{:<20}", "Aimbot(Hold)") << "[RM]" << "----------[" << (isAimbotOn ? "ON" : "OFF") << "]\n";
	std::cout << "========================================\n";
}

// responsible for handling input
void handleInput() {
	if (GetAsyncKeyState(VK_F1) & 1) {
		infAmmoNop.toggleNop();
		printUI();
	}

	if (GetAsyncKeyState(VK_F2) & 1) {
		TeamGodmodeDetour.toggleDetour();
		printUI();
	}

	if (GetAsyncKeyState(VK_F3) & 1) {
		InstaKillDetour.toggleDetour();
		printUI();
	}

	if ((GetAsyncKeyState(VK_RBUTTON) >> 15) & 1) {
		if (isAimbotOn == false) {
			isAimbotOn = true;
			printUI();
		}
		Aimbot(findClosestEnemy());
	} else {
		if (isAimbotOn == true) {
			isAimbotOn = false;
			printUI();
		}
	}

	if (GetAsyncKeyState(VK_F9) & 1) {
		toggleConsole();
		printUI();
	}

	if (GetAsyncKeyState(VK_F10) & 1) {
		mainHackLoopTramp.toggleTrampSBL();
		isHackOver = true;
	}


}

// a clean up function that runs after the dll is uninjected
void cleanUpHack(FILE *f) {
	if (infAmmoNop.isNopOn()) {
		infAmmoNop.toggleNop();
	}

	if (TeamGodmodeDetour.isHookOn()) {
		TeamGodmodeDetour.toggleDetour();
	}

	if (InstaKillDetour.isHookOn()) {
		InstaKillDetour.toggleDetour();
	}

	fclose(f);
	FreeConsole();
}

// Show/hide console
void toggleConsole() {
	static bool isConsoleShown = true;
	isConsoleShown = !isConsoleShown;

	if (isConsoleShown) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	} else {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

}

// create a console and redirect output to it
void setupConsole(FILE **f) {
	AllocConsole();
	freopen_s(f, "CONOUT$", "w", stdout);
}
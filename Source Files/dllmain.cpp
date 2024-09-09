// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <cstdio>
#include <chrono>
#include "HackFuncDeclarations.h"
#include "ConsoleAndInput.h"
#include "Globals.h"

void HackThread(HMODULE hModule);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void HackThread(HMODULE hModule) {
    FILE *f = nullptr;
    // create a console and redirect output
    setupConsole(&f);

    // setup the main hack loop
    mainHackLoopTramp.toggleTrampSBL();

    // The user interface is printed for the first time here
    printUI();

    while (!isHackOver) {
        // Ensures that this thread does not take up too much resources, also prevents UB
        Sleep(100);
    }

    cleanUpHack(f);

    FreeLibraryAndExitThread(hModule, 0);
}


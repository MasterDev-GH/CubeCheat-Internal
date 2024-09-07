// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "setupHooks.h"
#include "MainHackLoop.h"
#include <cstdio>
#include <chrono>
#include "ConsoleAndInput.h"

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
    FILE *f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);

    if (f == nullptr) {
        return;
    }

    setupHooks();

    mainHackLoopTramp.toggleTrampSBL();

    printUI();

    while (!isHackOver) {
        Sleep(100);
    }


    fclose(f);
    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);
}


#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include <GH3ML.hpp>
#include <MinHook.h>


#include <GH3ML/Hook.hpp>
#include <GH3ML/Log.hpp>

#include <filesystem>

#include <Gh3ml/Config.hpp>

#include "Main.hpp"

#include <d3d9.h>


extern gh3ml::LogSource gh3ml::internal::Log = gh3ml::LogSource("GH3ML");
extern gh3ml::LogSource gh3ml::internal::LogGH3 = gh3ml::LogSource("GH3");

uint32_t GetCFuncCount(void)
{
    return gh3ml::hook::Orig<0x004134a0, gh3ml::hook::cconv::CDecl, uint32_t>();
}


void gh3ml::internal::SetupCFuncRedirection()
{
    Log.Info("Setting up CFunc redirection...");

    //gh3ml::hook::CreateHook<0x004134a0, gh3ml::hook::cconv::CDecl>(GetCFuncCount);

    Log.Info("Finished setting up CFunc redirection.");
}

HANDLE _gh3Handle = nullptr;

const HANDLE gh3ml::GetGH3Handle()
{
    return _gh3Handle;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    _gh3Handle = GetCurrentProcess();



    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);

        gh3ml::Log::CreateConsole();

        gh3ml::internal::ReadConfig();
        if (MH_Initialize() != MH_OK)
            gh3ml::internal::Log.Error("Minhook failed to initialize!");
        else
            gh3ml::internal::Log.Info("Minhook initialized!");

        gh3ml::internal::SetupDefaultHooks();

        gh3ml::internal::Log.Info("Finished Core Initialization!");
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

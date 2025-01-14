#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include <GH3ML.hpp>
#include <Log.hpp>
#include <MinHook.h>

HANDLE _gh3Handle = nullptr;

const HANDLE gh3ml::GetGH3Handle()
{
    return _gh3Handle;
}



typedef void(__stdcall* func_Debug_Log)(char* fmt, ...);

func_Debug_Log Debug_Log = nullptr;
func_Debug_Log Debug_Log_Target = reinterpret_cast<func_Debug_Log>(0x00472b50);


void __stdcall detourDebugLog(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    std::cout << "GH3  | ";

    vprintf(fmt, args);
    
    std::cout << std::endl;

    Debug_Log(fmt, args);

    va_end(args);
}


HMODULE gh3Module = nullptr;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);

        gh3ml::Log::CreateConsole();

        if (MH_Initialize() != MH_OK)
        {
            // TODO: this
        }
        gh3ml::Log::Info("MinHook Initialized!");

        if (MH_CreateHook(reinterpret_cast<void**>(Debug_Log_Target), &detourDebugLog, reinterpret_cast<void**>(&Debug_Log)) != MH_OK)
        {
            std::cout << "Unable to get Hook!" << std::endl;
        }

        MH_EnableHook(reinterpret_cast<void**>(Debug_Log_Target));

        _gh3Handle = GetCurrentProcess();

        gh3ml::Log::Info("Finished Initializing!");
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
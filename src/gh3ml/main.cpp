#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include <GH3ML.hpp>
#include <MinHook.h>

#include "Main.hpp"

#include <GH3ML/Hook.hpp>
#include <GH3ML/Log.hpp>

#include <filesystem>


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

    Log.Info("Finished setting up CFunc redirection!");
}

HANDLE _gh3Handle = nullptr;

const HANDLE gh3ml::GetGH3Handle()
{
    return _gh3Handle;
}

using DebugLog = gh3ml::hook::Binding<0x00472b50, gh3ml::hook::cconv::CDecl, void, char*, va_list>;

void detourDebugLog(char* fmt, va_list args)
{
    gh3ml::internal::LogGH3.Info(fmt, args);

    DebugLog::Orig(fmt, args);
}

HWND detourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
    //if (lpClassName == "AspyrGH3")
        return gh3ml::hook::Orig<1, gh3ml::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, WS_POPUP, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    //else
    //    return gh3ml::hook::Orig<1, gh3ml::hook::cconv::STDCall, HWND>(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

struct QbStruct
{
    uint16_t member0;
    uint8_t member1;
    uint8_t member2;
    void* first;

    using InsertCStringItem = gh3ml::hook::Binding<0x00479ac0, gh3ml::hook::cconv::ThisCall, void, QbStruct*, uint32_t, const char*>;
    using InsertQbKeyItem = gh3ml::hook::Binding<0x00479c80, gh3ml::hook::cconv::ThisCall, void, QbStruct*, uint32_t, uint32_t>;
};

using LoadPak = gh3ml::hook::Binding<0x004a1780, gh3ml::hook::cconv::CDecl, bool, QbStruct*>;

int loadPakCount = 0;

bool detourLoadPak(QbStruct* qbStruct)
{
    auto ret = LoadPak::Orig(qbStruct);
    if (loadPakCount++ == 1)
    {
        if (std::filesystem::exists("../gh3ml/Mods/GH3Deluxe/pak/gh3dx.pak"))
        {
            QbStruct deluxeStruct = QbStruct();

            QbStruct::InsertCStringItem(&deluxeStruct, 0, "../gh3ml/Mods/GH3Deluxe/pak/gh3dx.pak");

            LoadPak::Orig(&deluxeStruct);
        }

    }
    return ret;
}

using CFuncPrintF = gh3ml::hook::Binding<0x00530940, gh3ml::hook::cconv::CDecl, bool, void*>;
bool detourCFuncPrintF(void* param1)
{

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    reinterpret_cast<void(*)(char*, size_t, void*)>(0x00532a80)(buffer, 1023, param1);


    // Replace linebreaks becuase we take care of them ourself
    for (auto i = 0; i < 1024; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = ' ';
        }
        if (buffer[i] == '\0')
            break;
    }

    gh3ml::internal::LogGH3.Info(buffer);
    //return gh3ml::hook::Orig<0x00530940, gh3ml::hook::cconv::CDecl, bool, char*>(param1);
    return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    _gh3Handle = GetCurrentProcess();

    QbStruct pakStruct = QbStruct();

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);

        gh3ml::Log::CreateConsole();

        if (MH_Initialize() != MH_OK)
            gh3ml::internal::Log.Error("Minhook failed to initialize!");
        else
            gh3ml::internal::Log.Info("Minhook initialized!");

        gh3ml::hook::CreateHook<DebugLog>(detourDebugLog);

        gh3ml::hook::CreateHook<1, gh3ml::hook::cconv::STDCall>(
            reinterpret_cast<uintptr_t>(GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA")),
            detourCreateWindowExA
        );

        gh3ml::hook::CreateHook<LoadPak>(detourLoadPak);
        gh3ml::hook::CreateHook<CFuncPrintF>(detourCFuncPrintF);

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

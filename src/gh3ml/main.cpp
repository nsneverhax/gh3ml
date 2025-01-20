#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include <GH3ML.hpp>
#include <MinHook.h>

#include "Main.hpp"

#include <gh3ml/Hook.hpp>


#include <GH3ML/Log.hpp>


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


typedef void(__stdcall* func_Debug_Log)(void* fmt, ...);
typedef HWND(__stdcall* func_CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID param);


void __cdecl detourDebugLog(char* fmt, va_list args)
{
    gh3ml::internal::LogGH3.Info(fmt, args);

    gh3ml::hook::Orig<0x00472b50, gh3ml::hook::cconv::CDecl, void, char*, va_list>(fmt, args);
}


func_CreateWindowExA CreateWindowExA_Orig = nullptr;
LPVOID targ = nullptr;

HWND __stdcall detourCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
   //if (lpClassName == "AspyrGH3")
        return ((func_CreateWindowExA)CreateWindowExA_Orig)(dwExStyle, lpClassName, lpWindowName, WS_POPUP, 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
   //else
     //   return ((func_CreateWindowExA)CreateWindowExA_Orig)(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}


struct QbStruct
{
    uint16_t member0;
    uint8_t member1;
    uint8_t member2;
    void* first;
};


typedef bool(__cdecl* func__LoadPak)(QbStruct* qbStruct);

func__LoadPak LoadPak_Original = nullptr;
func__LoadPak LoadPak_Target = reinterpret_cast<func__LoadPak>(0x004a1780);



typedef void(__thiscall* func__QbStruct_InsertCStringItem)(QbStruct* self, uint32_t key, const char* string);
typedef void(__thiscall* func__QbStruct_InsertQbKeyItem)(QbStruct* self, uint32_t key, uint32_t value);

func__QbStruct_InsertCStringItem QbStruct_InsertCStringItem = reinterpret_cast<func__QbStruct_InsertCStringItem>(0x00479ac0);
func__QbStruct_InsertQbKeyItem QbStruct_InsertQbKeyItem = reinterpret_cast<func__QbStruct_InsertQbKeyItem>(0x00479c80);

int loadPakCount = 0;

bool __cdecl detourLoadPak(QbStruct* qbStruct)
{
    bool ret = 0;
    ret = LoadPak_Original(qbStruct);
    if (loadPakCount == 1)
    {
        QbStruct deluxeStruct = QbStruct();

        QbStruct_InsertCStringItem(&deluxeStruct, 0, "../gh3ml/Mods/GH3Deluxe/pak/gh3dx.pak");

        LoadPak_Original(&deluxeStruct);

    }
    loadPakCount++;
    return ret;
}






HMODULE gh3Module = nullptr;



typedef uint32_t(* func__GetCFunCount)(void);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    _gh3Handle = GetCurrentProcess();

    targ = GetProcAddress(LoadLibraryA("user32.dll"), "CreateWindowExA");


    QbStruct pakStruct = QbStruct();

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
        gh3ml::internal::Log.Info("Minhook Initialized!");

        
        
        gh3ml::hook::CreateHook<0x00472b50, gh3ml::hook::cconv::CDecl>(detourDebugLog);

        if (MH_CreateHook(reinterpret_cast<void**>(targ), &detourCreateWindowExA, reinterpret_cast<void**>(&CreateWindowExA_Orig)) != MH_OK)
        {

        }



        if (MH_CreateHook(reinterpret_cast<void**>(LoadPak_Target), &detourLoadPak, reinterpret_cast<void**>(&LoadPak_Original)) != MH_OK)
        {

        }
        MH_EnableHook(reinterpret_cast<void**>(LoadPak_Target));
        MH_EnableHook(reinterpret_cast<void**>(0x00472b50));
        MH_EnableHook(reinterpret_cast<void**>(targ));

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
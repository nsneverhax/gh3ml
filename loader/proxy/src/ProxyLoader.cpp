#include <Windows.h>
#include <string>
#include <array>
#include <vector>
#include <filesystem>

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

// Vultu: We are going to provide the needed imports for GH3 from DINPUT8.dll since we are replacing it
// We are going to manually specify WINAPI (__stdcall) calling convention and then manually parse the decorated names
// into non-decorated ones. This is probably a bad idea, but it will work for now.


constexpr static auto MAX_PATH_CHARS = 32768u;
static HMODULE getDINPUT() 
{
    static auto xinput = []() -> HMODULE
        {
            std::wstring path(MAX_PATH_CHARS, L'\0');

            auto size = GetSystemDirectoryW(path.data(), path.size());
            if (size)
            {
                path.resize(size);
                return LoadLibraryW((path + L"\\DINPUT8.dll").c_str());
            }
            return NULL;
        }();

    return xinput;
}

static FARPROC getFP(const std::string& sym) 
{
    if (auto xinput = getDINPUT())
        return GetProcAddress(xinput, sym.c_str());

    return NULL;
}
#pragma comment(linker, "/export:DirectInput8Create@@YGJPAUHINSTANCE__@@KABU_GUID@@PAPAXPAUIUnknown@@@Z=DirectInput8Create,@5")
HRESULT WINAPI DirectInput8Create(HINSTANCE hinst,DWORD dwVersion,REFIID riidltf,LPVOID* ppvOut,LPUNKNOWN punkOuter)
{
    static auto fp = getFP("DirectInput8Create");
    if (fp)
    {
        using FPType = decltype(&DirectInput8Create);
        return reinterpret_cast<FPType>(fp)(hinst, dwVersion, riidltf, ppvOut, punkOuter);
    }

    return -1;
}

/*
#pragma comment(linker, "/export:XInputGetState@@YGKKPAUXINPUT_STATE@@@Z=XInputGetState,@2")
DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
    static auto fp = getFP("XInputGetState");
    if (fp) 
    {
        using FPType = decltype(&XInputGetState);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, pState);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputSetState@@YGKKPAUXINPUT_VIBRATION@@@Z=XInputSetState,@3")
DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
{
    static auto fp = getFP("XInputSetState");
    if (fp) 
    {
        using FPType = decltype(&XInputSetState);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, pVibration);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputGetCapabilities@@YGKKKPAUXINPUT_CAPABILITIES@@@Z=XInputGetCapabilities,@4")
DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities)
{
    static auto fp = getFP("XInputGetCapabilities");
    if (fp) 
    {
        using FPType = decltype(&XInputGetCapabilities);
        return reinterpret_cast<FPType>(fp)(dwUserIndex, dwFlags, pCapabilities);
    }

    return ERROR_DEVICE_NOT_CONNECTED;
}

#pragma comment(linker, "/export:XInputEnable@@YGXH@Z=XInputEnable,@5")
void WINAPI XInputEnable(BOOL enable)
{
    static auto fp = getFP("XInputEnable");
    if (fp) 
    {
        using FPType = decltype(&XInputEnable);
        reinterpret_cast<FPType>(fp)(enable);
    }

    return;
}
*/

// TODO: Vultu: this !!!!
static std::wstring getErrorString(DWORD error)
{
    return L"Could not load Geode! Error code: " + std::to_wstring(error);
}

// TODO: Vultu: this !!!!
static DWORD errorThread(LPVOID param) 
{
    constexpr wchar_t REDIST_ERROR[] = L"Could not load Geode!\n"
        "This is likely due to an outdated redist package.\n"
        "Do you want to update Microsoft Visual C++ Redistributable 2022 to try to fix this issue?";
    constexpr wchar_t ALT_REDIST_ERROR[] = L"Could not load Geode!\n\n"
        "Please **delete** the following files from your Geometry Dash directory and try again: ";
    const DWORD error = reinterpret_cast<DWORD64>(param);

    if (error == ERROR_DLL_INIT_FAILED) 
    {

    }
    else {
        MessageBoxW(NULL, getErrorString(error).c_str(), L"Load failed", MB_OK | MB_ICONWARNING);
    }

    return 0u;
}





BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);

        // This is UB. -- Vultu: Too bad!
        if (LoadLibraryW(L"nylon.dll") == NULL)
        {
            const auto param = reinterpret_cast<LPVOID>(static_cast<DWORD64>(GetLastError()));

            MessageBox(NULL, "LoadLibraryW returns NULL! The modloader will not be loaded.", "Unable to load \"nylon.dll\"", MB_OK);
            // CreateThread(NULL, 0, &errorThread, param, 0, NULL);
        }
    }
    

    return TRUE;
}

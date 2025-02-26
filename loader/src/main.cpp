#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include <MinHook.h>
#include <Nylon/Hook.hpp>
#include <Nylon/Log.hpp>
#include <filesystem>
#include <Nylon/Config.hpp>
#include <d3d9.h>

#include <Nylon/Internal/Main.hpp>
#include <Nylon/Internal/Logging/LogFile.hpp>


#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <Nylon/CommandConsole.hpp>


namespace fs = std::filesystem;
namespace in = nylon::internal;

nylon::LogSource in::Log = nylon::LogSource("Nylon");
nylon::LogSource in::LogGH3 = nylon::LogSource("GH3");
std::map<std::string, nylon::ModInfo> in::LoadedMods = { };


void in::LoadMods()
{
    Log.Info("Loading mods...");

    Log.Info("Loading mods from: \"{}\"", ModsDirectory().string());

    for (const auto& dir : fs::directory_iterator(ModsDirectory()))
    {
        auto infoPath = dir.path() / "modinfo.json";

        Log.Info("Checking for: \"{}\"...", infoPath.string());
        if (fs::exists(infoPath))
        {
            Log.Info("Loading...");
            ModInfo info = { };

            if (!ModInfo::TryRead(infoPath.string(), info))
            {
                Log.Error("Unable read load modinfo.json");
                continue;
            }
            else
            {
                LoadedMods.emplace(info.GetName(), info);
                Log.Info("Found mod: {}", info.GetName());
                in::ReadKeyAssociations(dir);
            }
        }

    }

    Log.Info("Finished loading mods.");
}

bool _isWine = false;
std::string _wineVersion = { };

bool nylon::IsWine()
{
    return _isWine;
}
std::string_view nylon::WineVersion()
{
    return _wineVersion;
}

HANDLE _gh3Handle = nullptr;
const HANDLE nylon::GH3Handle()
{
    return _gh3Handle;
}

constexpr int INST_NOP = 0x90;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

    // V: code stolen from https://gist.github.com/klange/282e62fdd1c2cae6a210443ccbc5b12f
    // will clean it up later
    static const char* (CDECL * pwine_get_version)(void);
    HMODULE hntdll = nullptr;

    _gh3Handle = GetCurrentProcess();

    // memset(reinterpret_cast<void*>(0x00401588), INST_NOP, 20);

    // nylon::WriteMemory(0x0060372f + 1, (uint8_t)0x5);

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:

        if (!fs::exists("no_wine"))
        {
            hntdll = GetModuleHandle("ntdll.dll");

            pwine_get_version = reinterpret_cast<const char* (__cdecl*)(void)>(GetProcAddress(hntdll, "wine_get_version"));

            _isWine = pwine_get_version != nullptr;
            if (pwine_get_version != nullptr)
                _wineVersion = { pwine_get_version() };

            if (_isWine)
            {
                nylon::WriteMemory((uintptr_t)(0x0057bb54 + 6), (uint8_t)0x1); // V: set 1 buffer for wine
            }
        }

        DisableThreadLibraryCalls(hinstDLL);

        in::CreateLogFile();

        if (nylon::IsWine())
            nylon::internal::Log.Info("Wine {} detected.", nylon::WineVersion());
        else
            nylon::internal::Log.Info("Wine was not detected. Assuming we are running on a Windows NT OS Please report this if this detection is an error.");

        in::ReadConfig();

        if (nylon::config::OpenConsole())
            nylon::Log::CreateConsole();
        
        in::ReadKeyAssociations(nylon::ResourcesDirectory());
        

        if (MH_Initialize() != MH_OK)
            in::Log.Error("Minhook failed to initialize!");
        else
            in::Log.Info("Minhook initialized!");

        in::SetupDefaultHooks();

       

        in::LoadMods();

        in::Log.Info("Finished Core Initialization!");
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
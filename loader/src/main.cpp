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
#include <Nylon/Internal/Hooks/Hooks.hpp>


#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>


#include <Nylon/CommandConsole.hpp>


#include <GH3/Spt/Singleton.hpp>


#include <Nylon/Checksum.hpp>
#include <stack>

namespace fs = std::filesystem;
namespace in = nylon::internal;

nylon::LogSource in::Log = nylon::LogSource("Nylon");
nylon::LogSource in::LogGH3 = nylon::LogSource("GH3");
std::map<std::string, nylon::ModInfo> in::LoadedMods = { };

std::stack<std::string_view> _logTaskStack = { };
void in::PushLogTask(std::string_view name)
{
    in::Log.Info("Starting Task: {}", name);
    _logTaskStack.push(name);
}
void in::PopLogTask()
{
    in::Log.Info("Finished Task: {}", _logTaskStack.top()); // mmff,. top..
    _logTaskStack.pop();
}

void in::LoadMods()
{
    PushLogTask("Loading Mods");

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

    PopLogTask();
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

    // TODO: this !!
    // int numArgs;
    // LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &numArgs);

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:

        DisableThreadLibraryCalls(hinstDLL);

        _gh3Handle = GetCurrentProcess();

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

        // V: We need to create the log as quickly as possible.

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
        in::SetupCEngineHooks();
        in::SetupGuitarFuncsHooks();

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
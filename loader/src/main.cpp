#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include "Main.hpp"
#include <MinHook.h>
#include <Nylon/Hook.hpp>
#include <Nylon/Log.hpp>
#include <filesystem>
#include <Nylon/Config.hpp>
#include <d3d9.h>

#include "Logging/LogFile.hpp"

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

#include <Nylon/CommandConsole.hpp>


namespace fs = std::filesystem;
namespace in = nylon::internal;

nylon::LogSource in::Log = nylon::LogSource("Nylon");
nylon::LogSource in::LogGH3 = nylon::LogSource("GH3");
std::map<std::string, nylon::ModInfo> in::LoadedMods = { };

std::map<GH3::CRCKey, char*> in::KeyAssociations = { };

void in::LoadMods()
{
    Log.Info("Loading mods...");

    Log.Info("Loading mods from: \"{}\"", ModsDirectory().string());

    for (const auto& dir : fs::directory_iterator(ModsDirectory()))
    {
        auto infoPath = dir.path().string() + "\\modinfo.json";

        Log.Info("Checking for: \"{}\"...", infoPath);
        if (fs::exists(infoPath))
        {
            Log.Info("Loading...");
            ModInfo info = { };

            if (!ModInfo::TryRead(infoPath, info))
            {
                Log.Error("Unable read load modinfo.json");
                continue;
            }
            else
            {
                LoadedMods.emplace(info.GetName(), info);
                Log.Info("Found mod: {}", info.GetName());
            }
        }

    }

    Log.Info("Finished loading mods.");
}

HANDLE _gh3Handle = nullptr;

const HANDLE nylon::GH3Handle()
{
    return _gh3Handle;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    _gh3Handle = GetCurrentProcess();

    fs::path filePath = { };

    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);

        in::CreateLogFile();

        filePath = in::LogFilePath();

        in::ReadConfig();

        if (nylon::Config::OpenConsole())
            nylon::Log::CreateConsole();

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

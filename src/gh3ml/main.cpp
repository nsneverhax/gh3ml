#include <Windows.h>
#include <intrin.h>

#include <iostream>

#include "Main.hpp"
#include <MinHook.h>
#include <GH3ML/Hook.hpp>
#include <GH3ML/Log.hpp>
#include <filesystem>
#include <Gh3ml/Config.hpp>
#include <d3d9.h>

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>


namespace fs = std::filesystem;

nylon::LogSource nylon::internal::Log = nylon::LogSource("GH3ML");
nylon::LogSource nylon::internal::LogGH3 = nylon::LogSource("GH3");
std::string nylon::internal::ModsPath = { };
std::map<std::string, nylon::ModInfo> nylon::internal::LoadedMods = { };
bool nylon::internal::IsImGuiActive = true;

void nylon::internal::LoadMods()
{
    Log.Info("Loading mods...");

    Log.Info("Loading mods from: \"%s\"", ModsPath.c_str());

    for (const auto& dir : fs::directory_iterator(ModsPath))
    {
        auto infoPath = dir.path().string() + "\\modinfo.json";

        Log.Info("Checking for: \"%s\"...", infoPath.c_str());
        if (fs::exists(infoPath))
        {
            Log.Info("Loading Mod from: \"%s\"", infoPath.c_str());
            ModInfo info = { };

            if (!ModInfo::TryRead(infoPath, info))
            {
                Log.Error("Unable to load mod.");
                continue;
            }
            else
            {
                LoadedMods.emplace(info.GetName(), info);
                Log.Info("Finished loading mod.");
            }
        }

    }

    Log.Info("Finished loading mods.");
}

void nylon::internal::SetupCFuncRedirection()
{
    Log.Info("Setting up CFunc redirection...");

    //gh3ml::hook::CreateHook<0x004134a0, gh3ml::hook::cconv::CDecl>(GetCFuncCount);

    Log.Info("Finished setting up CFunc redirection.");
}

HANDLE _gh3Handle = nullptr;

const HANDLE nylon::GetGH3Handle()
{
    return _gh3Handle;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    _gh3Handle = GetCurrentProcess();
    nylon::internal::ModsPath = std::filesystem::current_path().string() + "\\gh3ml\\Mods\\";



    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);

        nylon::Log::CreateConsole();

        nylon::internal::ReadConfig();
        if (MH_Initialize() != MH_OK)
            nylon::internal::Log.Error("Minhook failed to initialize!");
        else
            nylon::internal::Log.Info("Minhook initialized!");


        nylon::internal::SetupDefaultHooks();
        nylon::internal::LoadMods();

        nylon::internal::Log.Info("Finished Core Initialization!");
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

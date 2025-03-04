#include "Hooks.hpp"
#include <Nylon/Log.hpp>

#include <Nylon/Core.hpp>

namespace in = nylon::internal;

uint32_t detour__Aspyr_Win_Init(uint32_t param_1)
{
    return nylon::hook::Orig<in::KEY_ASPYR_WIN_INIT, nylon::hook::cconv::CDecl, uint32_t>(param_1);
}

double detour__Aspyr_Win_GetConfigNumberW(wchar_t* name, double fallback)
{
    return nylon::hook::Orig<in::KEY_ASPYR_GET_CONFIG_NUMBER_W, nylon::hook::cconv::CDecl, double>(name, fallback);
}
double detour__Aspyr_Win_GetConfigNumber(char* name, double fallback)
{
    return nylon::hook::Orig<in::KEY_ASPYR_GET_CONFIG_NUMBER, nylon::hook::cconv::CDecl, double>(name, fallback);
}
void in::SetupAspyrHooks()
{
    HMODULE AspyrModule = LoadLibraryA("AWL.dll"); // TODO: MOVE THIS

    in::Log.Info("Creating Aspyr hooks...");

    nylon::hook::CreateHook<KEY_ASPYR_WIN_INIT, nylon::hook::cconv::CDecl>(
        reinterpret_cast<uintptr_t>(GetProcAddress(AspyrModule, "?Init@Win@Aspyr@@YA?AW4Error@12@W4Mode@12@@Z")),
        detour__Aspyr_Win_Init
    );
    //nylon::hook::CreateHook<KEY_ASPYR_GET_CONFIG_NUMBER_W, nylon::hook::cconv::CDecl>(
    //    reinterpret_cast<uintptr_t>(GetProcAddress(AspyrModule, "?GetConfigNumber@Win@Aspyr@@YANPB_WN@Z")),
    //    detour__Aspyr_Win_GetConfigNumberW
    //);
    //nylon::hook::CreateHook<KEY_ASPYR_GET_CONFIG_NUMBER, nylon::hook::cconv::CDecl>(
    //    reinterpret_cast<uintptr_t>(GetProcAddress(AspyrModule, "?GetConfigNumber@Win@Aspyr@@YANPBDN@Z")),
    //    detour__Aspyr_Win_GetConfigNumber
    //);

    in::Log.Info("Finished creating Aspyr hooks");
}

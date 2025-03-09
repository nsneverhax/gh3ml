#include <Nylon/Internal/Hooks/Hooks.hpp>

using Nx_CEngine_sInitializeStartupParams = nylon::hook::Binding<0x0058c4c0, nylon::hook::cconv::CDecl, void>;

void detour__Nx_CEngine_sIntializeStartupParams()
{
	Nx_CEngine_sInitializeStartupParams::Orig();
}


void nylon::internal::SetupCEngineHooks()
{
	Log.Info("Setting up Nx::CEngine Hooks...");

	nylon::hook::CreateHook<Nx_CEngine_sInitializeStartupParams>(detour__Nx_CEngine_sIntializeStartupParams);

	Log.Info("Finished setting up Nx::CEngine hooks.");
}
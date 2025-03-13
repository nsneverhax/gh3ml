#include <nylon/Internal/Hooks/Hooks.hpp>
#include <nylon/Hooks/Gfx/CScreenFXManagerHooks.hpp>

#include <GH3/Script/CStruct.hpp>

void detour__Gfx_CScreenFXManager_AddScreenFXInstance(void* self, GH3::Script::CStruct* cstruct, GH3::undefined4 param_2)
{
    nylon::binding::Gfx_CScreenFXManager_AddScreenFXInstance::Orig(self, cstruct, param_2);
}
void nylon::internal::SetupGfxCScreenFXManagerHooks()
{
    PushLogTask("Creating Gfx::CScreenFXManager hooks");

    hook::CreateHook<nylon::binding::Gfx_CScreenFXManager_AddScreenFXInstance>(detour__Gfx_CScreenFXManager_AddScreenFXInstance);

    PopLogTask();
}
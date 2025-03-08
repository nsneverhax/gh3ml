#include "hooks/Hooks.hpp"
#include <Nylon/Checksum.hpp>

#include <GH3/Qb/QbStruct.hpp>

#include <GH3/Script/CSymbolTableEntry.hpp>

uint32_t mat_green = 0x46036C66;
uint32_t mat_red = 0xD803362A;
uint32_t mat_yellow = 0x7ECA1933;
uint32_t mat_blue = 0xAC903A3F;
uint32_t mat_orange = 0xD3541622;

uint32_t mat_hammer_orange = 0x7783E932;

GH3::CRCKey* NormalGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a178f4);

GH3::CRCKey* BattlePowerGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a178a4);
GH3::CRCKey* BattlePowerHammerGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a17890);

GH3::CRCKey* StarGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a178cc);
GH3::CRCKey* StarHammerGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a178b8);


GH3::CRCKey* ActiveGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a1787c);
GH3::CRCKey* ActiveHammerGemMaterialArray = reinterpret_cast<GH3::CRCKey*>(0x00a17868);

using GuitarFuncs_Create2DGem = nylon::hook::Binding<0x00432680, nylon::hook::cconv::CDecl, void, GH3::Script::CStruct*, int32_t, GH3::CRCKey, int32_t, float, int32_t, int32_t, void*>;

GH3::CRCKey keyList[] = {
	0xD803362A,
	0xD3541622,
	0x7ECA1933,
	0x46036C66,
	0xD3541622
};


float* GemStarScale = reinterpret_cast<float*>(0x00a130d0);

void detour__GuitarFuncs_Create2DGem(GH3::Script::CStruct* playerStatus, int32_t player, GH3::CRCKey colorKey, int32_t marker, float time, int32_t entry, int32_t gemCount, void* songArray)
{
	//NormalGemMaterialArray[0] = 0xD803362A;
	//NormalGemMaterialArray[1] = 0xD3541622;
	//NormalGemMaterialArray[2] = 0x7ECA1933;
	//NormalGemMaterialArray[3] = 0x46036C66;
	//NormalGemMaterialArray[4] = 0xD3541622;

	//for (auto i = 0; i < 5; i++)
	//{
	//	StarGemMaterialArray[i] = BattlePowerGemMaterialArray[i];
	//	StarHammerGemMaterialArray[i] = BattlePowerHammerGemMaterialArray[i];

	//	ActiveGemMaterialArray[i] = mat_orange;
	//	ActiveHammerGemMaterialArray[i] = mat_hammer_orange;

	//}

	GuitarFuncs_Create2DGem::Orig(playerStatus, player, colorKey, marker, time, entry, gemCount, songArray);
}


void nylon::internal::SetupGuitarFuncsHooks()
{
	Log.Info("Setting up GuitarFuncs Hooks...");

	nylon::hook::CreateHook<GuitarFuncs_Create2DGem>(detour__GuitarFuncs_Create2DGem);

	Log.Info("Finished setting up GuitarFuncs hooks.");
}
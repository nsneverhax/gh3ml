#pragma once

#include <Nylon/Core.hpp>

#include <GH3/Script/CScript.hpp>
#include <GH3/Script/CStruct.hpp>

namespace nylon::CFuncs
{
	extern bool PrintStructReportType;
	extern bool PrintStructReportName;

	using CFunction = bool(*)(GH3::Script::CStruct*, GH3::Script::CScript);

	// typedef CFunction = (bool)(*)(GH3::QbStruct*, GH3::QbScript*);
	bool IsNylon(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool ImGui_Begin(GH3::Script::CStruct* params, GH3::Script::CScript* script);

	bool SetConVar(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool GetConVar(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool HasConVar(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool RegisterConVar(GH3::Script::CStruct* params, GH3::Script::CScript* script);

	//bool SetPrintStructReportType(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	//bool GetPrintStructReportType(GH3::Script::CStruct* params, GH3::Script::CScript* script);

	//bool SetPrintStructReportName(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	//bool GetPrintStructReportName(GH3::Script::CStruct* params, GH3::Script::CScript* script);

	bool SetNylonFlag(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool GetNylonFlag(GH3::Script::CStruct* params, GH3::Script::CScript* script);

	bool IsBandAerosmith(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool IsSongAerosmith(GH3::Script::CStruct* params, GH3::Script::CScript* script);
	bool IsFiveBandSong(GH3::Script::CStruct* params, GH3::Script::CScript* script);
}
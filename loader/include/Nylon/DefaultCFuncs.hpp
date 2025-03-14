#pragma once

#include <Nylon/Core.hpp>
#include <GH3/Qb.hpp>

namespace nylon::CFuncs
{
	extern bool PrintStructReportType;
	extern bool PrintStructReportName;
	// typedef CFunction = (bool)(*)(GH3::QbStruct*, GH3::QbScript*);
	bool IsNylon(GH3::QbStruct* params, GH3::CScript* script);
	bool ImGui_Begin(GH3::QbStruct* params, GH3::CScript* script);

	bool SetConVar(GH3::QbStruct* params, GH3::CScript* script);
	bool GetConVar(GH3::QbStruct* params, GH3::CScript* script);
	bool HasConVar(GH3::QbStruct* params, GH3::CScript* script);
	bool RegisterConVar(GH3::QbStruct* params, GH3::CScript* script);

	bool SetPrintStructReportType(GH3::QbStruct* params, GH3::CScript* script);
	bool GetPrintStructReportType(GH3::QbStruct* params, GH3::CScript* script);

	bool SetPrintStructReportName(GH3::QbStruct* params, GH3::CScript* script);
	bool GetPrintStructReportName(GH3::QbStruct* params, GH3::CScript* script);
}
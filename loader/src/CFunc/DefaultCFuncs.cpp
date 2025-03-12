#include <Nylon/DefaultCFuncs.hpp>

#include <Nylon/CommandConsole.hpp>

#include <GH3/Script/CStruct.hpp>

namespace cf = nylon::CFuncs;

using namespace GH3::Script;

bool cf::SetConVar(GH3::Script::CStruct* params, CScript* script)
{
	std::string name = { };
	std::string desc = { };

	char* nameData = name.data();
	char* descData = name.data();

	params->GetNonLocalizedString(KEY_NAME, &nameData);
	params->GetNonLocalizedString(KEY_DESC, &descData);
	return true;
}
bool cf::GetConVar(GH3::Script::CStruct* params, CScript* script)
{
	return true;
}
bool cf::HasConVar(GH3::Script::CStruct* params, CScript* script)
{
	std::string name = { };

	char* nameData = name.data();

	return Console.HasConsoleCommand(name);
}
bool cf::RegisterConVar(GH3::Script::CStruct* params, CScript* script)
{
	return true;
}
extern bool cf::PrintStructReportType = true;

bool cf::SetPrintStructReportType(GH3::Script::CStruct* params, CScript * script)
{
	if (params->HasKey(KEY_TRUE))
		PrintStructReportType = true;
	else if (params->HasKey(KEY_FALSE))
		PrintStructReportType = false;
	return true;
}
bool cf::GetPrintStructReportType(GH3::Script::CStruct* params, CScript* script)
{
	return PrintStructReportType;
}

extern bool cf::PrintStructReportName = true;

bool cf::SetPrintStructReportName(GH3::Script::CStruct* params, CScript* script)
{
	if (params->HasKey(KEY_TRUE))
		PrintStructReportType = true;
	else if (params->HasKey(KEY_FALSE))
		PrintStructReportType = false;
	return true;
}
bool cf::GetPrintStructReportName(GH3::Script::CStruct* params, CScript* script)
{
	return PrintStructReportType;
}
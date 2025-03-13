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



bool cf::SetNylonFlag(GH3::Script::CStruct* params, GH3::Script::CScript* script)
{

	return true;
}
bool cf::GetNylonFlag(GH3::Script::CStruct* params, GH3::Script::CScript* script)
{

}

bool cf::IsBandAerosmith(GH3::Script::CStruct* params, GH3::Script::CScript* script)
{

}
bool cf::IsSongAerosmith(GH3::Script::CStruct* params, GH3::Script::CScript* script)
{

}
bool cf::IsFiveBandSong(GH3::Script::CStruct* params, GH3::Script::CScript* script)
{

}
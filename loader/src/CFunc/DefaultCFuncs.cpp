#include <Nylon/DefaultCFuncs.hpp>

#include <Nylon/CommandConsole.hpp>

namespace cf = nylon::CFuncs;

bool cf::SetConVar(GH3::QbStruct* params, GH3::CScript* script)
{
	std::string name = { };
	std::string desc = { };

	char* nameData = name.data();
	char* descData = name.data();

	params->GetString(KEY_NAME, &nameData);
	params->GetString(KEY_DESC, &descData);
	return true;
}
bool cf::GetConVar(GH3::QbStruct* params, GH3::CScript* script)
{
	return true;
}
bool cf::HasConVar(GH3::QbStruct* params, GH3::CScript* script)
{
	std::string name = { };

	char* nameData = name.data();

	return Console.HasConsoleCommand(name);
}
bool cf::RegisterConVar(GH3::QbStruct* params, GH3::CScript* script)
{
	return true;
}
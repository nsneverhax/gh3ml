#include "CFuncHooks.hpp"

#include <Nylon/Config.hpp>

#include <filesystem>

namespace binding = nylon::internal::binding;

bool PrintStruct(GH3::QbStruct* params, GH3::QbScript* script)
{
    // nylon::internal::LogGH3.Info("PrintStruct");
	return true;
}

bool PrintF(GH3::QbStruct* params, GH3::QbScript* script)
{
    if (!nylon::Config::AllowQScriptPrintf())
        return true;

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    reinterpret_cast<void(*)(char*, size_t, void*)>(0x00532a80)(buffer, 1023, params);

    // Replace linebreaks becuase we take care of them ourself
    for (auto i = 0; i < 1024; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = ' ';
        }
        if (buffer[i] == '\0')
            break;
    }

    nylon::internal::LogGH3.Info(buffer);

    return true;
}

bool LoadPak(GH3::QbStruct* params, GH3::QbScript* script)
{
    static bool _doPakCheck = true;

    auto ret = binding::CFunc_LoadPak::Orig(params, script);

    if (!_doPakCheck)
        return ret;

    char* pakNameBuffer;

    params->GetString(0, &pakNameBuffer, 0);

    if (strcmp("pak/qb.pak", pakNameBuffer) == 0)
    {
        for (const auto pair : nylon::internal::LoadedMods)
        {
            auto expectedPakPath = pair.second.GetDirectory() + "\\pak\\" + pair.first + ".pak";
            
            nylon::internal::Log.Info("Expecting: \"{}\"", expectedPakPath.c_str());
            
            if (!std::filesystem::exists(std::format("{}{}", (nylon::ModsDirectory() / expectedPakPath).string(), ".xen")))
            {
                nylon::internal::Log.Info("Unable to find pak file.");
                continue;
            }

            expectedPakPath.insert(0, "..\\nylon\\Mods\\");

            nylon::internal::Log.Info("Found it! Loading...");
            GH3::QbStruct modPakStruct = GH3::QbStruct();

            GH3::Functions::InsertCStringItem(&modPakStruct, 0, expectedPakPath.data());

            binding::CFunc_LoadPak::Orig(&modPakStruct, script);
            nylon::internal::Log.Info("Done!");
        }

        _doPakCheck = false;
    }

    return ret;
}


void nylon::internal::CreateCFuncHooks()
{
	hook::CreateHook<binding::CFunc_PrintStruct>(PrintStruct);
    hook::CreateHook<binding::CFunc_PrintF>(PrintF);
    hook::CreateHook<binding::CFunc_LoadPak>(LoadPak);
}
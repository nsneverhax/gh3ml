#include "CFuncHooks.hpp"

#include <Nylon/Config.hpp>

#include <filesystem>

namespace binding = nylon::internal::binding;

bool PrintStruct(GH3::QbStruct* params, GH3::QbScript* script)
{
    if (params->ComponentList == nullptr)
        nylon::internal::LogGH3.Warn("Struct had a null component list!!");

    GH3::CComponent* component = params->ComponentList;

    nylon::internal::LogGH3.Info("START PRINT STRUCT");
    while (component != nullptr)
    {
        switch (component->GetType())
        {
        case GH3::CComponentType::QFlagNone:
            nylon::internal::LogGH3.Info("None");
            break;
        case GH3::CComponentType::QFlagStructItem:
            nylon::internal::LogGH3.Info("QFlagStructItem");
            break;
        case GH3::CComponentType::QTypeInt:
            nylon::internal::LogGH3.Info("QTypeInt");
            break;
        case GH3::CComponentType::QTypeFloat:
            nylon::internal::LogGH3.Info("QTypeFloat");
            break;
        case GH3::CComponentType::QTypeCString:
            nylon::internal::LogGH3.Info("QTypeCString");
            break;
        case GH3::CComponentType::QTypeWString:
            nylon::internal::LogGH3.Info("QTypeWString");
            break;
        case GH3::CComponentType::QTypePair:
            nylon::internal::LogGH3.Info("QTypePair");
            break;
        case GH3::CComponentType::QTypeVector:
            nylon::internal::LogGH3.Info("QTypeVector");
            break;
        case GH3::CComponentType::QTypeScript:
            nylon::internal::LogGH3.Info("QTypeScript");
            break;
        case GH3::CComponentType::QTypeCFunc:
            nylon::internal::LogGH3.Info("QTypeCFunc");
            break;
        case GH3::CComponentType::QTypeUnk9:
            nylon::internal::LogGH3.Info("QTypeUnk9");
            break;
        case GH3::CComponentType::QTypeQbStruct:
            nylon::internal::LogGH3.Info("QTypeQbStruct");
            break;
        case GH3::CComponentType::QTypeQbArray:
            nylon::internal::LogGH3.Info("QTypeQbArray");
            break;
        case GH3::CComponentType::QTypeQbKey:
            nylon::internal::LogGH3.Info("QTypeQbKey");
            break;
        case GH3::CComponentType::QTypeQbKeyRef:
            nylon::internal::LogGH3.Info("QTypeQbKeyRef");
            break;
        case GH3::CComponentType::QTypeUnk20:
            nylon::internal::LogGH3.Info("QTypeUnk20");
            break;
        case GH3::CComponentType::QTypeUnk21:
            nylon::internal::LogGH3.Info("QTypeUnk21");
            break;
        case GH3::CComponentType::QTypeBinaryTree1:
            nylon::internal::LogGH3.Info("QTypeBinaryTree1");
            break;
        case GH3::CComponentType::QTypeBinaryTree2:
            nylon::internal::LogGH3.Info("QTypeBinaryTree2");
            break;
        case GH3::CComponentType::QTypeStringPointer:
            nylon::internal::LogGH3.Info("QTypeStringPointer");
            break;
        case GH3::CComponentType::QTypeMap:
            nylon::internal::LogGH3.Info("QTypeMap");
            break;
        default:
            nylon::internal::LogGH3.Info("UNKNOWN TYPE: {:X}", (uint8_t)component->GetType());
            break;
        }
        component = component->Next;
    }
    nylon::internal::LogGH3.Info("END PRINT STRUCT");
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
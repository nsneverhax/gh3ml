#include "CFuncHooks.hpp"

#include <Nylon/Config.hpp>

#include <filesystem>

#include <codecvt>

#include <GH3/CRC.hpp>

namespace binding = nylon::internal::binding;

namespace in = nylon::internal;

bool PrintStruct(GH3::QbStruct* params, GH3::CScript* script)
{
    if (params->ComponentList == nullptr)
        nylon::internal::LogGH3.Warn("Struct had a null component list!!");

    GH3::Script::CComponent * component = params->ComponentList;


    //nylon::internal::LogGH3.Info("START PRINT STRUCT");
    nylon::internal::LogGH3.Info("{");
    while (component != nullptr)
    {
        GH3::Script::CComponentType type = component->GetType(); // V: leave this for debugging
        auto it = in::KeyAssociations.find(component->Key);

        std::string key = GH3::CRC::FindChecksumName(component->Key);
        in::LogGH3.Info(key.append(" -> "));
        switch (type)
        {
        case GH3::Script::CComponentType::QFlagNone:
            in::LogGH3.Info("  None (Unmoved Type: {:X})", ((uint8_t)component->Flags));
            break;
        case GH3::Script::CComponentType::QFlagStructItem:
            in::LogGH3.Info("  QFlagStructItem (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeInt:
            in::LogGH3.Info("  QTypeInt : {}", component->IntegerValue);
            break;
        case GH3::Script::CComponentType::QTypeFloat:
            in::LogGH3.Info("  QTypeFloat : {}", component->FloatValue);
            break;
        case GH3::Script::CComponentType::QTypeCString:
            in::LogGH3.Info("  QTypeCString : \"{}\"", component->CStringValue);
            break;
        case GH3::Script::CComponentType::QTypeWString:
            //in::LogGH3.Debug("(QTypeWString are converted to UTF-8 strings and may yield incorrect results, please report this)");
            in::LogGH3.Info("  QTypeWString : \"{}\"", 
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(std::wstring(component->WStringValue))
            );
            break;
        case GH3::Script::CComponentType::QTypePair:
            in::LogGH3.Info("  QTypePair : ({0}, {1})", component->PairValue->X, component->PairValue->Y);
            break;
        case GH3::Script::CComponentType::QTypeVector:
            in::LogGH3.Info("  QTypeVector : {0}, {1}, {2}, {3}", component->VectorPair->X, component->VectorPair->Y, component->VectorPair->Z, component->VectorPair->W);
            break;
        case GH3::Script::CComponentType::QTypeScript:
            in::LogGH3.Info("  QTypeScript : (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeCFunc:
            in::LogGH3.Info("  QTypeCFunc : (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeUnk9:
            in::LogGH3.Info("  QTypeUnk9 : (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeQbStruct:
            in::LogGH3.Info("  QTypeQbStruct : ");
            in::LogGH3.SetIndentLevel(in::LogGH3.GetIndentLevel() + 1);
            PrintStruct(component->StructValue, script);
            in::LogGH3.SetIndentLevel(in::LogGH3.GetIndentLevel() - 1);
            break;
        case GH3::Script::CComponentType::QTypeQbArray:
            in::LogGH3.Info("  QTypeQbArray : Type:\"{0}\" Size:{1}", GH3::Script::to_string(component->GetType()), component->ArrayValue->size);
            break;
        case GH3::Script::CComponentType::QTypeQbKey:
            in::LogGH3.Info("  QTypeQbKey : {:#06x}", component->KeyValue);
            break;
        case GH3::Script::CComponentType::QTypeQbKeyRef:
            in::LogGH3.Info("  QTypeQbKeyRef (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeUnk20:
            in::LogGH3.Info("  QTypeUnk20 (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeUnk21:
            in::LogGH3.Info("  QTypeUnk21 (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeBinaryTree1:
            in::LogGH3.Info("  QTypeBinaryTree1 (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeBinaryTree2:
            in::LogGH3.Info("  QTypeBinaryTree2 (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeStringPointer:
            in::LogGH3.Info("  QTypeStringPointer (not implemented, please report this to Vultu with your code!)");
            break;
        case GH3::Script::CComponentType::QTypeMap:
            in::LogGH3.Info("  QTypeMap (not implemented, please report this to Vultu with your code!)");
            break;
        default:
            in::LogGH3.Info("  UNKNOWN TYPE: {:X}", (uint8_t)component->GetType());
            break;
        }
        component = component->Next;
    }    
    nylon::internal::LogGH3.Info("}");
    //nylon::internal::LogGH3.Info("END PRINT STRUCT");
	return true;
}

bool PrintF(GH3::QbStruct* params, GH3::CScript* script)
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

    // nylon::internal::LogGH3.Info(buffer);

    return true;
}

bool LoadPak(GH3::QbStruct* params, GH3::CScript* script)
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
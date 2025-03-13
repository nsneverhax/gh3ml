#include <Nylon/Internal/Hooks/Hooks.hpp>

#include <Nylon/Config.hpp>

#include <filesystem>

#include <codecvt>

#include <GH3/CRC.hpp>
#include <Nylon/DefaultCFuncs.hpp>
#include <GH3/Script/CStruct.hpp>

namespace binding = nylon::internal::binding;

namespace in = nylon::internal;

using namespace GH3::Script;

bool detour__CFunc_PrintStruct(GH3::Script::CStruct* params, GH3::Script::CScript* script)
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

        std::string key = "";

        bool reportName = true;
        bool reportType = true;

        if (!reportName && !reportType)
            key = "";
        else if (reportName && !reportType)
            key = std::format("{} : ", GH3::CRC::FindChecksumName(component->Key));
        else if (!reportName && reportType)
            key = std::format("{} : ", GH3::Script::to_string(component->GetType()));
        else
            key = std::format("{} ({}) : ", GH3::CRC::FindChecksumName(component->Key), GH3::Script::to_string(component->GetType()));

        switch (type)
        {
        case GH3::Script::CComponentType::QFlagNone:
            in::LogGH3.Info("\t{}(Unmoved Type: {:X}) ((report this to vultu!!!)", key, ((uint8_t)component->Flags));
            break;
        case GH3::Script::CComponentType::QFlagStructItem:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeInt:
            in::LogGH3.Info("\t{}{}", key, component->IntegerValue);
            break;
        case GH3::Script::CComponentType::QTypeFloat:
            in::LogGH3.Info("\t{}{}", key, component->FloatValue);
            break;
        case GH3::Script::CComponentType::QTypeCString:
            in::LogGH3.Info("\t{}\"{}\"", key, component->CStringValue);
            break;
        case GH3::Script::CComponentType::QTypeWString:
            //in::LogGH3.Debug("(QTypeWString are converted to UTF-8 strings and may yield incorrect results, please report this)");
            in::LogGH3.Info("\t{}\"{}\"", key,
                std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(std::wstring(component->WStringValue))
            );
            break;
        case GH3::Script::CComponentType::QTypePair:
            in::LogGH3.Info("\t{0}({1}, {2})", key, component->PairValue->X, component->PairValue->Y);
            break;
        case GH3::Script::CComponentType::QTypeVector:
            in::LogGH3.Info("\t{0}({1}, {2}, {3}, {4})", key, component->VectorValue->X, component->VectorValue->Y, component->VectorValue->Z, component->VectorValue->W);
            break;
        case GH3::Script::CComponentType::QTypeScript:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeCFunc:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeUnk9:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeQbStruct:
            in::LogGH3.Info("\t{}", key);
            in::LogGH3.SetIndentLevel(in::LogGH3.GetIndentLevel() + 1);
            detour__CFunc_PrintStruct(component->StructValue, script);
            in::LogGH3.SetIndentLevel(in::LogGH3.GetIndentLevel() - 1);
            break;
        case GH3::Script::CComponentType::QTypeQbArray:
            in::LogGH3.Info("\t{0}Type:\"{1}\" Size:{2}", key, GH3::Script::to_string(component->GetType()), component->ArrayValue->size);
            break;
        case GH3::Script::CComponentType::QTypeQbKey:
            in::LogGH3.Info("\t{}", GH3::CRC::FindChecksumName(component->KeyValue));
            break;
        case GH3::Script::CComponentType::QTypeQbKeyRef:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeUnk20:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeUnk21:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeBinaryTree1:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeBinaryTree2:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeStringPointer:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        case GH3::Script::CComponentType::QTypeMap:
            in::LogGH3.Info("\t{}(not implemented, please report this to Vultu with your code!)", key);
            break;
        default:
            in::LogGH3.Info("\t{0}UNKNOWN TYPE: {:X}", key, (uint8_t)component->GetType());
            break;
        }
        component = component->Next;
    }    
    nylon::internal::LogGH3.Info("}");
    //nylon::internal::LogGH3.Info("END PRINT STRUCT");
	return true;
}

bool detour__CFunc_PrintF(GH3::Script::CStruct* params, CScript* script)
{
    if (!nylon::config::AllowQScriptPrintf())
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

bool detour__CFunc_LoadPak(GH3::Script::CStruct* params, CScript* script)
{
    static bool _doPakCheck = true;

    auto ret = binding::CFunc_LoadPak::Orig(params, script);

    if (!_doPakCheck)
        return ret;

    char* pakNameBuffer;

    params->GetNonLocalizedString(0, &pakNameBuffer, 0);

    in::Log.Info("Loading Pak: \"{}\"", pakNameBuffer);

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
            GH3::Script::CStruct modPakStruct = GH3::Script::CStruct();

            modPakStruct.AddNonLocalizedString(0, expectedPakPath.data());

            binding::CFunc_LoadPak::Orig(&modPakStruct, script);
            nylon::internal::Log.Info("Done!");
        }

        _doPakCheck = false;
    }

    return ret;
}

bool detour__CFunc_LoadTexture(GH3::Script::CStruct* params, CScript* script)
{
    char* nameBuffer;

    params->GetNonLocalizedString(0, &nameBuffer, 0);

    in::Log.Info("Loading Texture: \"{}\"", nameBuffer);

    return binding::CFunc_LoadTexture::Orig(params, script);
}

#include <Nylon/Profile.hpp>

nylon::Profile temp = { };


bool detour__CFuncs_SetGemConstants(GH3::Script::CStruct* params, CScript* script)
{
    auto ret = binding::CFuncs_SetGemConstants::Orig(params, script);

    GH3::CRCKey* DefaultMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a178f4);
    GH3::CRCKey* DefaultHOPOMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a178e0);

    GH3::CRCKey* StarPhraseMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a178cc);
    GH3::CRCKey* StarPhraseHOPOMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a178b8);

    GH3::CRCKey* BattlePhraseMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a178a4);
    GH3::CRCKey* BattlePhraseHOPOMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a17890);

    GH3::CRCKey* ActivePowerMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a1787c);
    GH3::CRCKey* ActivePowerHOPOMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a17868);

    GH3::CRCKey* WhammyMaterials = reinterpret_cast<GH3::CRCKey*>(0x00a1791c);

    // GH3::CRCKey* GemColorKeys = reinterpret_cast<GH3::CRCKey*>(0x00957b90);

    //GemColorKeys[0] = GH3::CRC::GenerateCRCFromString("Red");
    //GemColorKeys[1] = GH3::CRC::GenerateCRCFromString("Orange");
    //GemColorKeys[2] = GH3::CRC::GenerateCRCFromString("Yellow");
    //GemColorKeys[3] = GH3::CRC::GenerateCRCFromString("Green");
    //GemColorKeys[4] = GH3::CRC::GenerateCRCFromString("Blue");

    for (auto i = 0; i < 5; i++)
    {
        auto laneMaterial = temp.GetGuitarLaneMaterialInfo(static_cast<nylon::HighwayLane>(i));
        DefaultMaterials[i] = laneMaterial.DefaultGems.Strum;
        DefaultHOPOMaterials[i] = laneMaterial.DefaultGems.HOPO;

        StarPhraseMaterials[i] = laneMaterial.StarPowerPhraseGems.Strum;
        StarPhraseHOPOMaterials[i] = laneMaterial.StarPowerPhraseGems.HOPO;

        BattlePhraseMaterials[i] = laneMaterial.BattlePowerPhraseGems.Strum;
        BattlePhraseHOPOMaterials[i] = laneMaterial.BattlePowerPhraseGems.HOPO;

        ActivePowerMaterials[i] = laneMaterial.StarPowerGems.Strum;
        ActivePowerHOPOMaterials[i] = laneMaterial.StarPowerGems.HOPO;

        WhammyMaterials[i] = laneMaterial.SustainMaterial;

        // in::Log.Info("WhammyMaterials[{}] : {}", i, GH3::CRC::FindChecksumName(WhammyMaterials[i]));
        // 
        //in::Log.Info("DefaultMaterials[{}] : {:#8}", i, (DefaultMaterials[i]));
        //in::Log.Info("DefaultHOPOMaterials[{}] : {:#8}", i, (DefaultHOPOMaterials[i]));

        //in::Log.Info("StarPhraseMaterials[{}] : {:#8}", i, (StarPhraseMaterials[i]));
        //in::Log.Info("StarPhraseHOPOMaterials[{}] : {:#8}", i, (StarPhraseHOPOMaterials[i]));

        //in::Log.Info("BattlePhraseMaterials[{}] : {:#8}", i, (BattlePhraseMaterials[i]));
        //in::Log.Info("BattlePhraseHOPOMaterials[{}] : {:#8}", i, (BattlePhraseHOPOMaterials[i]));

        //in::Log.Info("ActivePowerMaterials[{}] : {:#8}", i, (ActivePowerMaterials[i]));
        //in::Log.Info("ActivePowerHOPOMaterials[{}] : {:#8}", i, (ActivePowerHOPOMaterials[i]));
    }

    return ret;
}

void nylon::internal::CreateCFuncHooks()
{
    PushLogTask("Creating CFunc hooks");

    temp.SetDefaults();

	hook::CreateHook<binding::CFunc_PrintStruct>(detour__CFunc_PrintStruct);
    hook::CreateHook<binding::CFunc_PrintF>(detour__CFunc_PrintF);
    hook::CreateHook<binding::CFunc_LoadPak>(detour__CFunc_LoadPak);
    hook::CreateHook<binding::CFunc_LoadTexture>(detour__CFunc_LoadTexture);
    hook::CreateHook<binding::CFuncs_SetGemConstants>(detour__CFuncs_SetGemConstants);

    PopLogTask();
}
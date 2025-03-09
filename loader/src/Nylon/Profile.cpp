#include <Nylon/Profile.hpp>
#include <Nylon/Checksum.hpp>
#include <Nylon/Internal/Main.hpp>
#include <matjson.hpp>

#include <fstream>

namespace nylon
{
	std::filesystem::path ProfilesDirectory()
	{
		return NylonDirectory() / "Profiles";
	}



	void Profile::SetDefaults()
	{
		/*
			DefaultMaterials[0] : sys_Gem2D_Green_sys_Gem2D_Green
			DefaultHOPOMaterials[0] : sys_Gem2D_Green_hammer_sys_Gem2D_Green_hammer
			StarPhraseMaterials[0] : sys_Star2D_Green_sys_Star2D_Green
			StarPhraseHOPOMaterials[0] : sys_Star2D_Green_Hammer_sys_Star2D_Green_Hammer
			BattlePhraseMaterials[0] : sys_BattleGEM_Green01_sys_BattleGEM_Green01
			BattlePhraseHOPOMaterials[0] : sys_BattleGEM_Hammer_Green01_sys_BattleGEM_Hammer_Green01
			ActivePowerMaterials[0] : sys_Gem2D_StarPower_sys_Gem2D_StarPower
			ActivePowerHOPOMaterials[0] : sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer

			DefaultMaterials[1] : sys_Gem2D_Red_sys_Gem2D_Red
			DefaultHOPOMaterials[1] : sys_Gem2D_Red_hammer_sys_Gem2D_Red_hammer
			StarPhraseMaterials[1] : sys_Star2D_Red_sys_Star2D_Red
			StarPhraseHOPOMaterials[1] : sys_Star2D_Red_Hammer_sys_Star2D_Red_Hammer
			BattlePhraseMaterials[1] : sys_BattleGEM_RED01_sys_BattleGEM_RED01
			BattlePhraseHOPOMaterials[1] : sys_BattleGEM_Hammer_RED01_sys_BattleGEM_Hammer_RED01
			ActivePowerMaterials[1] : sys_Gem2D_StarPower_sys_Gem2D_StarPower
			ActivePowerHOPOMaterials[1] : sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer

			DefaultMaterials[2] : sys_Gem2D_Yellow_sys_Gem2D_Yellow
			DefaultHOPOMaterials[2] : sys_Gem2D_Yellow_hammer_sys_Gem2D_Yellow_hammer
			StarPhraseMaterials[2] : sys_Star2D_Yellow_sys_Star2D_Yellow
			StarPhraseHOPOMaterials[2] : sys_Star2D_Yellow_Hammer_sys_Star2D_Yellow_Hammer
			BattlePhraseMaterials[2] : sys_BattleGEM_Yellow01_sys_BattleGEM_Yellow01
			BattlePhraseHOPOMaterials[2] : sys_BattleGEM_Hammer_Yellow01_sys_BattleGEM_Hammer_Yellow01
			ActivePowerMaterials[2] : sys_Gem2D_StarPower_sys_Gem2D_StarPower
			ActivePowerHOPOMaterials[2] : sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer

			DefaultMaterials[3] : sys_Gem2D_Blue_sys_Gem2D_Blue
			DefaultHOPOMaterials[3] : sys_Gem2D_Blue_hammer_sys_Gem2D_Blue_hammer
			StarPhraseMaterials[3] : sys_Star2D_Blue_sys_Star2D_Blue
			StarPhraseHOPOMaterials[3] : sys_Star2D_Blue_Hammer_sys_Star2D_Blue_Hammer
			BattlePhraseMaterials[3] : sys_BattleGEM_Blue01_sys_BattleGEM_Blue01
			BattlePhraseHOPOMaterials[3] : sys_BattleGEM_Hammer_Blue01_sys_BattleGEM_Hammer_Blue01
			ActivePowerMaterials[3] : sys_Gem2D_StarPower_sys_Gem2D_StarPower
			ActivePowerHOPOMaterials[3] : sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer

			DefaultMaterials[4] : sys_Gem2D_Orange_sys_Gem2D_Orange
			DefaultHOPOMaterials[4] : sys_Gem2D_Orange_hammer_sys_Gem2D_Orange_hammer
			StarPhraseMaterials[4] : sys_Star2D_Orange_sys_Star2D_Orange
			StarPhraseHOPOMaterials[4] : sys_Star2D_Orange_Hammer_sys_Star2D_Orange_Hammer
			BattlePhraseMaterials[4] : sys_BattleGEM_Orange01_sys_BattleGEM_Orange01
			BattlePhraseHOPOMaterials[4] : sys_BattleGEM_Hammer_Orange01_sys_BattleGEM_Hammer_Orange01
			ActivePowerMaterials[4] : sys_Gem2D_StarPower_sys_Gem2D_StarPower
			ActivePowerHOPOMaterials[4] : sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer

			WhammyMaterials[0] : sys_Whammy2D_Green_sys_Whammy2D_Green
			WhammyMaterials[1] : sys_Whammy2D_Red_sys_Whammy2D_Red
			WhammyMaterials[2] : sys_Whammy2D_Yellow_sys_Whammy2D_Yellow
			WhammyMaterials[3] : sys_Whammy2D_Blue_sys_Whammy2D_Blue
			WhammyMaterials[4] : sys_Whammy2D_Orange_sys_Whammy2D_Orange

			*/



		//const char* laneNames[5]
		//{
		//	"Green",
		//	"Red",
		//	"Yellow",
		//	"Blue",
		//	"Orange"
		//};

		const char* laneNames[5]
		{
			"Red",
			"Orange",
			"Yellow",
			"Green",
			"Blue"
		};
		for (auto i = 0; i < 5; i++)
		{
			m_guitarLaneMaterialInfoList[i].DefaultGems.Strum = GH3::CRC::GenerateCRCFromString(std::format("sys_Gem2D_{0}_sys_Gem2D_{0}", laneNames[i]).c_str());
			m_guitarLaneMaterialInfoList[i].DefaultGems.HOPO = GH3::CRC::GenerateCRCFromString(std::format("sys_Gem2D_{0}_hammer_sys_Gem2D_{0}_hammer", laneNames[i]).c_str());

			m_guitarLaneMaterialInfoList[i].StarPowerPhraseGems.Strum = GH3::CRC::GenerateCRCFromString(std::format("sys_Star2D_{0}_sys_Star2D_{0}", laneNames[i]).c_str());
			m_guitarLaneMaterialInfoList[i].StarPowerPhraseGems.HOPO = GH3::CRC::GenerateCRCFromString(std::format("sys_Star2D_{0}_hammer_sys_Star2D_{0}_hammer", laneNames[i]).c_str());

			m_guitarLaneMaterialInfoList[i].BattlePowerPhraseGems.Strum = GH3::CRC::GenerateCRCFromString(std::format("sys_BattleGEM_{0}01_sys_BattleGEM_{0}01", laneNames[i]).c_str());
			m_guitarLaneMaterialInfoList[i].BattlePowerPhraseGems.HOPO = GH3::CRC::GenerateCRCFromString(std::format("sys_BattleGEM_Hammer_{0}01_sys_BattleGEM_Hammer_{0}01", laneNames[i]).c_str());

			m_guitarLaneMaterialInfoList[i].StarPowerGems.Strum = GH3::CRC::GenerateCRCFromString("sys_Gem2D_StarPower_sys_Gem2D_StarPower");
			m_guitarLaneMaterialInfoList[i].StarPowerGems.HOPO = GH3::CRC::GenerateCRCFromString("sys_Gem2D_StarPower_hammer_sys_Gem2D_StarPower_hammer");

			m_guitarLaneMaterialInfoList[i].SustainMaterial = GH3::CRC::GenerateCRCFromString(std::format("sys_Whammy2D_{0}_sys_Whammy2D_{0}", laneNames[i]).c_str());

		}
	}


	bool Profile::SetName(std::string_view name)
	{
		m_name = name;
		return true;
	}
	std::string_view Profile::GetName() const
	{
		return m_name;
	}
	bool Profile::SetGuitarLaneMaterialInfo(HighwayLane lane, const GuitarLaneMaterialInfo& info)
	{
		m_guitarLaneMaterialInfoList[static_cast<uint32_t>(lane)] = { info };
		return true;
	}
	const GuitarLaneMaterialInfo& Profile::GetGuitarLaneMaterialInfo(HighwayLane lane) const
	{
		return m_guitarLaneMaterialInfoList[static_cast<uint32_t>(lane)];
	}


	inline matjson::Value makeGuitarGemMaterialInfo(const GuitarGemMaterialInfo& gemInfo)
	{
		return matjson::makeObject({
				{ "strum", gemInfo.Strum },
				{ "hopo", gemInfo.HOPO },
				{ "open", gemInfo.Open },
			});
	}
	inline matjson::Value makeGuitarLaneObject(const GuitarLaneMaterialInfo& laneInfo)
	{
		return matjson::makeObject({
				{ "defaultGems", makeGuitarGemMaterialInfo(laneInfo.DefaultGems) },
				{ "starPowerPhraseGems", makeGuitarGemMaterialInfo(laneInfo.StarPowerPhraseGems) },
				{ "battlePowerPhraseGems", makeGuitarGemMaterialInfo(laneInfo.BattlePowerPhraseGems) },
				{ "starPowerGems", makeGuitarGemMaterialInfo(laneInfo.StarPowerGems) },
			});
	}
	bool Profile::Write(std::filesystem::path path, const Profile& profile)
	{
		try
		{
			nylon::internal::PushLogTask(std::format("Writing Profile: {}", profile.GetName()));

			auto obj = matjson::makeObject(
				{
					{ "name", profile.GetName()},
					{ "sustainTailSizeMultiplier", 1.0f },

					{ "highwayGuitarLaneInfo", matjson::makeObject({
							{ "greenGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Green)) },
							{ "redGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Red)) },
							{ "yellowGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Yellow)) },
							{ "blueGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Blue)) },
							{ "orangeGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Orange)) },
							{ "openGemLane", makeGuitarLaneObject(profile.GetGuitarLaneMaterialInfo(HighwayLane::Open)) },
						}),
					}
				});

			auto dumped = obj.dump();
			std::ofstream dumpFile(path);

			dumpFile << dumped.c_str();
			dumpFile.close();

			return true;
		}
		catch (...)
		{
			nylon::internal::PopLogTask();
			return false;
		}
	}
}
#pragma once

#include <Nylon/Core.hpp>
#include <GH3/Common.hpp>

namespace nylon
{
	/// <summary>
	/// The current directory where Nylon will look for profiles
	/// </summary>
	/// <returns></returns>
	std::filesystem::path ProfilesDirectory();

	enum class HighwayLane
	{
		Green,
		Red,
		Yellow,
		Blue,
		Orange,
		Open
	};

	struct GuitarGemMaterialInfo
	{
		GuitarGemMaterialInfo()
		{

		}
		GuitarGemMaterialInfo(const GuitarGemMaterialInfo& src)
		{
			Strum = src.Strum;
			HOPO = src.HOPO;
			Open = src.Open;
		}

		GH3::CRCKey Strum = 0;
		GH3::CRCKey HOPO = 0;
		GH3::CRCKey Open = 0;
	};

	struct GuitarLaneMaterialInfo
	{
		GuitarLaneMaterialInfo()
		{

		}
		GuitarLaneMaterialInfo(const GuitarLaneMaterialInfo& src)
		{
			DefaultGems = { src.DefaultGems };
			StarPowerPhraseGems = { src.StarPowerPhraseGems };
			BattlePowerPhraseGems = { src.BattlePowerPhraseGems };
			StarPowerGems = { src.StarPowerGems };
			SustainMaterial = src.SustainMaterial;
		}

		/// <summary>
		/// Gems to use when no effect is active
		/// </summary>
		GuitarGemMaterialInfo DefaultGems = { };
		/// <summary>
		/// Gems to use when a star power phrase is active
		/// </summary>
		GuitarGemMaterialInfo StarPowerPhraseGems = { };
		/// <summary>
		/// Gems to use when a battle power phrase is active
		/// </summary>
		GuitarGemMaterialInfo BattlePowerPhraseGems = { };
		/// <summary>
		/// Gems to use when star power is active
		/// </summary>
		GuitarGemMaterialInfo StarPowerGems = { };

		GH3::CRCKey SustainMaterial = 0;
	};

	class Profile
	{
	private:
		GuitarLaneMaterialInfo m_guitarLaneMaterialInfoList[6];
		std::string m_name = "Default";

	public:
		void SetDefaults();


		bool SetName(std::string_view name);
		std::string_view GetName() const;

		bool SetGuitarLaneMaterialInfo(HighwayLane lane, const GuitarLaneMaterialInfo& info);
		const GuitarLaneMaterialInfo& GetGuitarLaneMaterialInfo(HighwayLane lane) const;

		static bool Write(std::filesystem::path path, const Profile& profile);
		static bool Read(std::filesystem::path path, Profile& profile);
	};


}
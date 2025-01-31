#pragma once

#include <string>

namespace gh3ml
{
	enum class ModTag
	{
		Unspecified = 0x0000,
		Highway		= 0x0001,
		Song		= 0x0002,
		Model		= 0x0004,
		Gameplay	= 0x0008,
		BugFix		= 0x0010,
		Performance	= 0x0020,
		UI			= 0x0040,
		Utility		= 0x0080,
		Joke		= 0x0100,
		Paid		= 0x0200,
	};

	class ModInfo
	{
	private:
		std::string m_name = "axelsteelsawesomemod";
		std::string m_author = "Axel Steel";
		std::string m_displayName = "My Mod";
		std::string m_description = "GH3 Modding in 2025??";
		std::string m_version = "1.0.0.0";
		std::string m_directory = { };

		ModTag m_tags = ModTag::Unspecified;
	public:
		static bool TryRead(const std::string& filepath, ModInfo& info);

		/// <summary>
		/// Gets the name of the mod, it's unique identifer
		/// </summary>
		/// <returns></returns>
		const std::string& GetName() const;
		/// <summary>
		/// Gets the author of the mod, who made it
		/// </summary>
		/// <returns></returns>
		const std::string& GetAuthor() const;

		/// <summary>
		/// Gets the display name of the mod, the pretty name the end users will see
		/// </summary>
		/// <returns></returns>
		const std::string& GetDisplayName() const;

		/// <summary>
		/// Gets the description of the mod, text with information about the mod
		/// </summary>
		/// <returns></returns>
		const std::string& GetDescription() const;

		/// <summary>
		/// Gets the version of the mod
		/// </summary>
		/// <returns></returns>
		const std::string& GetVersion() const;

		/// <summary>
		/// Gets the tags of the mod, the categories the mod fits in with
		/// </summary>
		/// <returns></returns>
		const ModTag& GetTags() const;

		/// <summary>
		/// Gets the directory of the mod, where to find it's modinfo.json
		/// </summary>
		/// <returns></returns>
		const std::string& GetDirectory() const;
	};
}
#pragma once

#include <cstdint>
#include <string>

namespace nylon
{
	enum class VersionType
	{
		Alpha,
		Beta,
		Release_Candidate,
		Release
	};

	struct VersionInfo
	{
		VersionInfo()
		{

		}
		VersionInfo(uint32_t major, uint32_t minor, uint32_t revision, VersionType type)
		{
			Major = major;
			Minor = minor;
			Revision = revision;
			Type = type;
		}
		inline bool operator==(const VersionInfo& rhs)
		{
			return (Major == rhs.Major) && (Minor == rhs.Minor) && (Revision == rhs.Revision) && (Type == rhs.Type);
		}
		inline bool operator!=(const VersionInfo& rhs)
		{
			return (Major != rhs.Major) || (Minor != rhs.Minor) || (Revision != rhs.Revision) || (Type != rhs.Type);
		}
		inline bool operator<(const VersionInfo& rhs)
		{
			if (Type < rhs.Type)
				return true;
			if (Major < rhs.Major)
				return true;
			if (Minor < rhs.Minor)
				return true;
			if (Revision < rhs.Revision)
				return true;

			return false;
		}
		inline bool operator>(const VersionInfo& rhs)
		{
			if (Type > rhs.Type)
				return true;
			if (Major > rhs.Major)
				return true;
			if (Minor > rhs.Minor)
				return true;
			if (Revision > rhs.Revision)
				return true;

			return false;
		}
		inline bool operator<=(const VersionInfo& rhs)
		{
			if (Type <= rhs.Type)
				return true;
			if (Major <= rhs.Major)
				return true;
			if (Minor <= rhs.Minor)
				return true;
			if (Revision <= rhs.Revision)
				return true;

			return false;
		}
		inline bool operator>=(const VersionInfo& rhs)
		{
			if (Type >= rhs.Type)
				return true;
			if (Major >= rhs.Major)
				return true;
			if (Minor >= rhs.Minor)
				return true;
			if (Revision >= rhs.Revision)
				return true;

			return false;
		}

		uint32_t Major = 0;
		uint32_t Minor = 0;
		uint32_t Revision = 0;
		VersionType Type = VersionType::Alpha;
	};

	// Vultu: VERSIONING RULES:
	// Major : a change resulting in API differences that are not backwards compatible
	// Minor : a change resulting in API differences that are backwards compatible
	// Revision : backwards compatible bug fixes


	/// <summary>
	/// The current Nylon version
	/// </summary>
	/// <returns></returns>
	const VersionInfo& Version();

	bool IsPreRelease();

	std::string to_string(VersionType value, bool shortHand = false);
	std::string to_string(const VersionInfo& value);
}
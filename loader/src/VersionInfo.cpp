#include <Nylon/VersionInfo.hpp>
#include <format>

nylon::VersionInfo _currentVersion = { 1, 5, 0, nylon::VersionType::Alpha };
bool _isPreRelease = true;

const nylon::VersionInfo& nylon::Version()
{
	return _currentVersion;
}
bool nylon::IsPreRelease()
{
	return _isPreRelease;
}
std::string nylon::to_string(VersionType value, bool shortHand)
{
	switch (value)
	{
	case nylon::VersionType::Alpha:
		return shortHand ? "a" : "Alpha";
	case nylon::VersionType::Beta:
		return shortHand ? "b" : "Beta";
	case nylon::VersionType::Release_Candidate:
		return shortHand ? "rc" : "Release Candidate";
	case nylon::VersionType::Release:
		return shortHand ? "r" : "Release";
	default:
		return shortHand ? "u" : "Unknown";
	}
}
std::string nylon::to_string(const VersionInfo& value)
{
	return std::format("{}{}.{}.{}-{}", _isPreRelease ? "pre-" : "", to_string(value.Type), value.Major, value.Minor, value.Revision);
}
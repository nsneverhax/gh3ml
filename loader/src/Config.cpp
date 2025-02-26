#include <Nylon/Internal/Main.hpp>

#include <Nylon/Config.hpp>

#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

namespace fs = std::filesystem;
namespace in = nylon::internal;
namespace cfg = nylon::config;

nylon::VersionInfo _versionInfo = { };

bool _unlockFPS = false;
bool _openConsole = false;
bool _allowScriptPrintf = false;
cfg::WindowStyle _windowStyle = cfg::WindowStyle::Fullscreen;

bool _configMalformed = false;

void UnwrapValue(matjson::Value& value, std::string_view name, bool* outValue, bool defaultValue)
{
	if (outValue == nullptr)
		return;

	*outValue = defaultValue;
	try
	{
		if (!value.contains(name.data()))
			return;

		*outValue = value[name.data()].asBool().unwrap();

		return;
	}
	catch (...)
	{
		in::Log.Warn("Config Variable: {} was malformed.", name);
		_configMalformed = true;
		return;
	}
}
void UnwrapValue(matjson::Value& value, std::string_view name, uint32_t* outValue, uint32_t defaultValue)
{
	if (outValue == nullptr)
		return;

	*outValue = defaultValue;
	try
	{
		if (!value.contains(name.data()))
			return;

		*outValue = value[name.data()].asUInt().unwrap();

		return;
	}
	catch (...)
	{
		in::Log.Warn("Config Variable: {} was malformed.", name);
		_configMalformed = true;
		return;
	}
}

void in::ReadConfig()
{
	_configMalformed = false;

	if (!fs::exists(cfg::ConfigFilepath()))
	{
		in::Log.Warn("Unable to find \"{}\" so it will be remade.", cfg::ConfigFilepath().string());
		in::WriteConfig();
		return;
	}

	std::ifstream t(cfg::ConfigFilepath().c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();

	auto result = matjson::parse(buffer);

	if (!result)
	{
		in::Log.Warn("Unable to parse \"{}\" so it will be remade.", cfg::ConfigFilepath().string());
		in::WriteConfig();
		return;
	}

	matjson::Value object = result.unwrap();

	if (object.contains("versionInfo"))
	{
		auto versionValue = object["versionInfo"];
		UnwrapValue(versionValue, "major", &_versionInfo.Major, nylon::Version().Major);
		UnwrapValue(versionValue, "minor", &_versionInfo.Minor, nylon::Version().Minor);
		UnwrapValue(versionValue, "revision", &_versionInfo.Revision, nylon::Version().Revision);
		UnwrapValue(versionValue, "type", reinterpret_cast<uint32_t*>(&_versionInfo.Type), (uint32_t)nylon::Version().Type);

		if (_versionInfo != nylon::Version())
			_configMalformed = true;
	}
	else
		_configMalformed = true;

	UnwrapValue(object, "unlockfps", &_unlockFPS, false);
	UnwrapValue(object, "openGH3Console", &_openConsole, true);
	UnwrapValue(object, "allowQScriptPrintf", &_allowScriptPrintf, true);

	UnwrapValue(object, "windowStyle", reinterpret_cast<uint32_t*>(&_windowStyle), (uint32_t)cfg::WindowStyle::Windowed);

	if (_configMalformed)
	{
		in::Log.Warn("\"{}\" was malformed or the version didn't match, so it will be remade using known values.", cfg::ConfigFilepath().string());
		WriteConfig();
	}
}

void in::WriteConfig()
{
	try
	{
		auto obj = matjson::makeObject(
			{
				{ "openGH3Console", true },
				{ "allowQScriptPrintf", true },
				{ "windowStyle", 1 },
				{ "pluginLogType", 1 },
				{ "unlockfps", false },
				{ "versionInfo", matjson::makeObject({
					{ "major", nylon::Version().Major},
					{ "minor", nylon::Version().Minor },
					{ "revision", nylon::Version().Revision },
					{ "type", (uint32_t)nylon::Version().Type },
					}),

				}
			}
		);

		auto dumped = obj.dump();
		std::ofstream dumpFile(nylon::NylonDirectory() / "config.json");

		dumpFile << dumped.c_str();
		dumpFile.close();
	}
	catch (...)
	{
		Log.Error("There was an unknown error writing the config file!");
	}
}

std::map<GH3::CRCKey, std::string> in::KeyAssociations = { };

void in::ReadKeyAssociations(std::filesystem::path path)
{
	in::Log.Info("Checking \"{}\" for keys...", path.string());

	auto filepath = path / "QBKeys.txt";

	if (!std::filesystem::exists(filepath))
	{
		in::Log.Info("Did not find \"{}\"", filepath.string());
		return;
	}

	if (std::filesystem::is_directory(filepath))
	{
		in::Log.Warn("Found \"{}\" but it was a directory.", filepath.string());
		return;
	}
	in::Log.Warn("Found \"{}\" ", filepath.string());

	std::ifstream file = { };

	std::string checksumBuffer = { };
	std::string nameBuffer = { };
	bool readingChecksum = false;

	try
	{
		file.open(filepath);

		if (file.fail() || file.bad())
		{
			in::Log.Warn("Failed to open \"{}\" failbit: 0x{:X04} badbit: 0x{:X04}", filepath.string(), file.failbit, file.badbit);
			file.close();
			return;
		}

		uint32_t lineNumber = 0;
		for (std::string line = { }; std::getline(file, line); lineNumber++)
		{
			checksumBuffer = { };
			nameBuffer = { };
			readingChecksum = true;

			for (std::string::iterator it = line.begin(); it != line.end(); it++)
			{
				bool whiteSpace = *it == ' ' || *it == '\t';

				if (whiteSpace)
				{
					if (checksumBuffer.empty())
						continue; // V: probably just padding. probably.
					else
						readingChecksum = false;
				}
				else
				{
					if (readingChecksum)
						checksumBuffer += *it;
					else
						nameBuffer += *it;
				}
			}

			if (checksumBuffer.empty() || nameBuffer.empty())
			{
				in::Log.Warn("Unable to convert line {} to a key/value pair. Checksum: \"{}\" Name: \"{}\"", lineNumber + 1, checksumBuffer, nameBuffer);
				continue;
			}
			std::size_t pos = 0;
			uint32_t checksum = 0;

			// V: There is no good "try convert" like C# :<
			try
			{
				checksum = std::stoul(checksumBuffer, &pos, (checksumBuffer.starts_with("0x") || checksumBuffer.starts_with("0X")) ? 16 : 10);
			}
			catch (std::invalid_argument const& ex)
			{
				in::Log.Warn("Unable to convert \"{}\" on line {} to a valid checksum: Invalid Argument", checksumBuffer, lineNumber + 1);
				continue;
			}
			catch (std::out_of_range const& ex)
			{
				in::Log.Warn("Unable to convert \"{}\" on line {} to a valid checksum: Out of Range", checksumBuffer, lineNumber + 1);
				continue;
			}

			if (checksum == 0)
			{
				in::Log.Warn("An unknown error resulted in a null checksum (\"{}\") on line {}", checksumBuffer, lineNumber + 1);
				continue;
			}

			if (!in::KeyAssociations.contains(checksum))
				in::KeyAssociations.insert({ static_cast<GH3::CRCKey>(checksum), nameBuffer });
		}

		file.close();

		in::Log.Info("Successfully parsed \"{}\"", path.string());
		return;
	}
	catch (...)
	{
		in::Log.Error("An unknown error occured when parsing \"{}\" Open: {}", filepath.string(), file.is_open());

		if (file.is_open())
			file.close();
		return;
	}

}

std::filesystem::path cfg::ConfigFilepath()
{
	return nylon::NylonDirectory() / "config.json";
}

const nylon::VersionInfo& cfg::Version()
{
	return _versionInfo;
}

bool cfg::UnlockFPS()
{
	return _unlockFPS;
}

bool cfg::OpenConsole()
{
	return _openConsole;
}
bool cfg::AllowQScriptPrintf()
{
	return _allowScriptPrintf;
}
cfg::WindowStyle cfg::GameWindowStyle()
{
	return _windowStyle;
}
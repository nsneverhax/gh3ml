#include <Nylon/ModInfo.hpp>
#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

bool nylon::ModInfo::TryRead(const std::filesystem::path& filepath, ModInfo& modInfo)
{
	modInfo.m_directory = std::filesystem::path(filepath).parent_path().filename().string();

	std::ifstream stream(filepath);
	std::stringstream buffer;
	buffer << stream.rdbuf();
	stream.close();

	auto result = matjson::parse(buffer);

	if (!result)
	{
		std::cout << "READ ERROR" << std::endl;
		return false;
	}
	matjson::Value object = result.unwrap();

	if (!object.contains("name") || 
		!object.contains("author") || 
		!object.contains("displayName") || 
		!object.contains("description") || 
		!object.contains("version") ||
		!object.contains("tags"))
		return false;

	modInfo.m_name = object["name"].asString().unwrap();
	modInfo.m_author = object["author"].asString().unwrap();
	modInfo.m_displayName = object["displayName"].asString().unwrap();
	modInfo.m_description = object["description"].asString().unwrap();
	modInfo.m_version = object["version"].asString().unwrap();
	modInfo.m_tags = static_cast<ModTag>(object["tags"].asUInt().unwrap());

	return true;
}

const std::string& nylon::ModInfo::GetName() const
{
	return m_name;
}

const std::string& nylon::ModInfo::GetAuthor() const
{
	return m_author;
}

const std::string& nylon::ModInfo::GetDisplayName() const
{
	return m_displayName;
}

const std::string& nylon::ModInfo::GetDescription() const
{
	return m_description;
}

const std::string& nylon::ModInfo::GetVersion() const
{
	return m_version;
}

const nylon::ModTag& nylon::ModInfo::GetTags() const
{
	return m_tags;
}

const std::string& nylon::ModInfo::GetDirectory() const
{
	return m_directory;
}

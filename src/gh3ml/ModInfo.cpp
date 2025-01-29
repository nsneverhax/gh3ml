#include <GH3ML/ModInfo.hpp>
#include <matjson.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

bool gh3ml::ModInfo::TryRead(const std::string& filepath, ModInfo& modInfo)
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

const std::string& gh3ml::ModInfo::GetName() const
{
	return m_name;
}

const std::string& gh3ml::ModInfo::GetAuthor() const
{
	return m_author;
}

const std::string& gh3ml::ModInfo::GetDisplayName() const
{
	return m_displayName;
}

const std::string& gh3ml::ModInfo::GetDescription() const
{
	return m_description;
}

const std::string& gh3ml::ModInfo::GetVersion() const
{
	return m_version;
}

const gh3ml::ModTag& gh3ml::ModInfo::GetTags() const
{
	return m_tags;
}

const std::string& gh3ml::ModInfo::GetDirectory() const
{
	return m_directory;
}
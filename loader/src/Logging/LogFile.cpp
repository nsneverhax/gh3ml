#include "LogFile.hpp"

#include <Nylon/Core.hpp>

namespace fs = std::filesystem;
fs::path logFilePath = { };

std::ofstream logStream = { };

fs::path nylon::internal::LogFilePath()
{
	return logFilePath;
}

void nylon::internal::CreateLogFile()
{
	if (!fs::exists(LogDirectory()) || !fs::is_directory(LogDirectory()))
		fs::create_directory(LogDirectory());
	
	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

	for (const auto& entry : fs::directory_iterator(LogDirectory()))
	{
		if (entry.path().filename().string().starts_with("latest"))
		{
			std::string newName = entry.path().filename().string();
			newName = newName.substr(newName.find_first_of('-') + 1);
			fs::rename(entry.path(), LogDirectory() / newName);
		}
	}

	logFilePath = LogDirectory() / std::format("latest-{:%H-%M-%OS %d-%m-%Y}.log", time);

	logStream.open(logFilePath.string());
}

std::ofstream& nylon::internal::LogStream()
{
	return logStream;
}
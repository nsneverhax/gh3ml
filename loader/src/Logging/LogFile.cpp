#include "LogFile.hpp"

#include <Nylon/Core.hpp>
#include <Nylon/TimePoint.hpp>

namespace fs = std::filesystem;
fs::path logFilePath = { };

std::ofstream logStream = { };

fs::path nylon::internal::LogFilePath()
{
	return logFilePath;
}

bool nylon::internal::CreateLogFile()
{
	try
	{
		if (!fs::exists(LogDirectory()) || !fs::is_directory(LogDirectory()))
			fs::create_directory(LogDirectory());


		for (const auto& entry : fs::directory_iterator(LogDirectory()))
		{
			if (entry.path().filename().string().starts_with("latest"))
			{
				std::string newName = entry.path().filename().string();
				newName = newName.substr(newName.find_first_of('-') + 1);
				fs::rename(entry.path(), LogDirectory() / newName);
			}
		}

		auto now = nylon::TimePoint::LocalNow();

		logFilePath = LogDirectory() / std::format("latest-{}-{}-{} {}-{}-{}.log", now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);
		
		logStream.open(logFilePath.string());
		return logStream.is_open();
	}
	catch (...)
	{
		std::cout << "There was an unknown error creating the log file." << std::endl;
		return false;
	}
}

std::ofstream& nylon::internal::LogStream()
{
	return logStream;
}
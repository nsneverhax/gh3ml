#include <Nylon/Internal/Main.hpp>

#include <Nylon/Internal/Logging/LogFile.hpp>

#include <Nylon/Core.hpp>
#include <Nylon/TimePoint.hpp>

namespace fs = std::filesystem;
namespace in = nylon::internal;

fs::path logFilePath = { };

std::ofstream logStream = { };

fs::path in::LogFilePath()
{
	return logFilePath;
}

bool in::CreateLogFile()
{
	in::Log.Debug("Creating log file...");
	try
	{
		if (!fs::exists(LogsDirectory()) || !fs::is_directory(LogsDirectory()))
		{
			in::Log.Debug("Creating log directory: {}", LogsDirectory().string());
			fs::create_directory(LogsDirectory());
		}


		for (const auto& entry : fs::directory_iterator(LogsDirectory()))
		{
			if (entry.path().filename().string().starts_with("latest"))
			{
				std::string newName = entry.path().filename().string();
				newName = newName.substr(newName.find_first_of('-') + 1);
				fs::rename(entry.path(), LogsDirectory() / newName);
			}
		}

		auto now = nylon::TimePoint::LocalNow();

		logFilePath = LogsDirectory() / std::format("latest-{}-{}-{} {}-{}-{}.log", now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);
		
		logStream.open(logFilePath.string());

		in::Log.Debug("Finished creating log file.");

		return logStream.is_open();
	}
	catch (...)
	{
		std::cout << "There was an unknown error creating the log file." << std::endl;

		return false;
	}
}

std::ofstream& in::LogStream()
{
	return logStream;
}
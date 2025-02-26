#include "LogFile.hpp"

#include <Nylon/Core.hpp>

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

		if (nylon::IsWine())
		{
			if (fs::exists(LogDirectory() / std::format("latest.log")))
				fs::remove(LogDirectory() / std::format("latest.log"));

			logFilePath = LogDirectory() / std::format("latest.log");
		}
		else
		{
			for (const auto& entry : fs::directory_iterator(LogDirectory()))
			{
				if (entry.path().filename().string().starts_with("latest"))
				{
					std::string newName = entry.path().filename().string();
					newName = newName.substr(newName.find_first_of('-') + 1);
					fs::rename(entry.path(), LogDirectory() / newName);
				}
			}

			auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

			logFilePath = LogDirectory() / std::format("latest-{:%H-%M-%OS %d-%m-%Y}.log", time);
		}
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
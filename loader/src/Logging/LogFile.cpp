#include "LogFile.hpp"

#include <Nylon/Core.hpp>

namespace fs = std::filesystem;
fs::path logFilePath = { };

std::ofstream logStream = { };

fs::path nylon::internal::GetLogFilePath()
{
	return logFilePath;
}

void nylon::internal::CreateLogFile()
{
	if (!fs::exists(LogDirectory()) || !fs::is_directory(LogDirectory()))
		fs::create_directory(LogDirectory());
	
	const auto now = std::chrono::system_clock::now();

	logFilePath = LogDirectory() / std::format("{:%H:%M:%OS %d-%m-%Y}.log", now);

	logStream.open(logFilePath.string(), std::ofstream::out | std::ofstream::ate | std::ofstream::trunc);
}

std::ofstream& nylon::internal::LogStream()
{
	return logStream;
}
#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

namespace nylon::internal
{
	std::filesystem::path GetLogFilePath();
	void CreateLogFile();
	std::ofstream& LogStream();
}
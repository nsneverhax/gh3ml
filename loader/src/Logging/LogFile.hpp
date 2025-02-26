#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <chrono>

namespace nylon::internal
{
	std::filesystem::path LogFilePath();
	bool CreateLogFile();
	std::ofstream& LogStream();
}
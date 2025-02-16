#pragma once

#include <Windows.h>
#include <format>
#include <chrono>
#include <iostream>

#ifdef ERROR
#undef ERROR
#endif // ERROR

namespace nylon::Log
{
	enum class LogLevel
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR
	};

	void AdjustConsoleBuffer(int16_t minLength);
	bool RedirectConsoleIO();
	
	
	
	LogLevel GetLogLevel();
	void SetLogLevel(LogLevel level);
	
	bool CreateConsole();
	bool ReleaseConsole();
	
	void WriteToOutput(LogLevel level, const char* sourceName, const char* message);

}
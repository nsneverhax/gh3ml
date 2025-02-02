#include <Nylon/LogSource.hpp>
#include <Nylon/Log.hpp>

#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#undef ERROR

nylon::LogSource::LogSource(const char* name)
{
	_name = name;
}
nylon::LogSource::LogSource(const std::string& name)
{
	_name = name;
}

void nylon::LogSource::Write(Log::LogLevel level, const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(level, _name.data(), fmt, args);

	va_end(args);
}

void nylon::LogSource::Trace(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt, args);

	va_end(args);
}
void nylon::LogSource::Debug(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt, args);

	va_end(args);
}
void nylon::LogSource::Info(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt, args);

	va_end(args);
}
void nylon::LogSource::Warn(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt, args);

	va_end(args);
}
void nylon::LogSource::Error(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt, args);

	va_end(args);
}


void nylon::LogSource::Write(Log::LogLevel level, const char* fmt, va_list args) const
{
	Log::WriteToOutput(level, _name.data(), fmt, args);
}
void nylon::LogSource::Trace(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt, args);
}
void nylon::LogSource::Debug(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt, args);
}
void nylon::LogSource::Info(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt, args);
}
void nylon::LogSource::Warn(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt, args);
}

void nylon::LogSource::Error(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt, args);
}

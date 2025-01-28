#include <GH3ML/LogSource.hpp>
#include <GH3ML/Log.hpp>

#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#undef ERROR

gh3ml::LogSource::LogSource(const char* name)
{
	_name = name;
}
gh3ml::LogSource::LogSource(const std::string& name)
{
	_name = name;
}

void gh3ml::LogSource::Write(Log::LogLevel level, const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(level, _name.data(), fmt, args);

	va_end(args);
}

void gh3ml::LogSource::Trace(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt, args);

	va_end(args);
}
void gh3ml::LogSource::Debug(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt, args);

	va_end(args);
}
void gh3ml::LogSource::Info(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt, args);

	va_end(args);
}
void gh3ml::LogSource::Warn(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt, args);

	va_end(args);
}
void gh3ml::LogSource::Error(const char* fmt, ...) const
{
	va_list args;
	va_start(args, fmt);

	Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt, args);

	va_end(args);
}


void gh3ml::LogSource::Write(Log::LogLevel level, const char* fmt, va_list args) const
{
	Log::WriteToOutput(level, _name.data(), fmt, args);
}
void gh3ml::LogSource::Trace(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt, args);
}
void gh3ml::LogSource::Debug(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt, args);
}
void gh3ml::LogSource::Info(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt, args);
}
void gh3ml::LogSource::Warn(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt, args);
}

void gh3ml::LogSource::Error(const char* fmt, va_list args) const
{
	Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt, args);
}
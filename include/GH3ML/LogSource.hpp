#pragma once

#include <cstdint>
#include <string>

#include <GH3ML/Log.hpp>

namespace gh3ml
{
	class LogSource
	{
	private:
		std::string_view _name = { "NO NAME" };

	public:
		LogSource(const char* name);
		LogSource(const std::string& name);

		void Write(Log::LogLevel level, const char* fmt, ...) const;

		void Trace(const char* fmt, ...) const;
		void Debug(const char* fmt, ...) const;
		void Info(const char* fmt, ...) const;
		void Warn(const char* fmt, ...) const;
		void Error(const char* fmt, ...) const;


		void Write(Log::LogLevel level, const char* fmt, va_list args) const;

		void Trace(const char* fmt, va_list args) const;
		void Debug(const char* fmt, va_list args) const;
		void Info(const char* fmt, va_list args) const;
		void Warn(const char* fmt, va_list args) const;
		void Error(const char* fmt, va_list args) const;
	};
}
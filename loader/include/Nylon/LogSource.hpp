#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <format>

#include <Nylon/Log.hpp>

namespace nylon
{
	class LogSource
	{
	private:
		std::string_view _name = { "NO NAME" };
		uint32_t _indentLevel = 0;
	public:
		LogSource(const char* name);
		LogSource(const std::string& name);

		void SetIndentLevel(uint32_t level);
		uint32_t GetIndentLevel() const;

		std::string_view GetName();

		/*
		template<typename... Args>
		void WriteLine(Log::LogLevel level, const char* fmt, Args&&... args) const
		{
			// TODO: THIS!
			//Log::WriteToOutput(level, _name.data(), fmt, args...);
		}
		*/

		template<class... Args>
		void Trace(std::string& fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		template<class... Args>
		void Trace(const char* fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		void Trace(std::string_view fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt.data(), _indentLevel);
		}
		void Trace(const char* fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::TRACE, _name.data(), fmt, _indentLevel);
		}


		template<class... Args>
		void Debug(std::string& fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		template<class... Args>
		void Debug(const char* fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		void Debug(std::string_view fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt.data(), _indentLevel);
		}
		void Debug(const char* fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::DEBUG, _name.data(), fmt, _indentLevel);
		}


		template<class... Args>
		void Info(std::string& fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		template<class... Args>
		void Info(const char* fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		void Info(std::string_view fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt.data(), _indentLevel);
		}
		void Info(const char* fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::INFO, _name.data(), fmt, _indentLevel);
		}


		template<class... Args>
		void Warn(std::string& fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		template<class... Args>
		void Warn(const char* fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		void Warn(std::string_view fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt.data(), _indentLevel);
		}
		void Warn(const char* fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::WARN, _name.data(), fmt, _indentLevel);
		}


		template<class... Args>
		void Error(std::string& fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		template<class... Args>
		void Error(const char* fmt, Args&&... args) const
		{
			Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), std::vformat(fmt, std::make_format_args(args...)).c_str(), _indentLevel);
		}
		void Error(std::string_view fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt.data(), _indentLevel);
		}
		void Error(const char* fmt) const
		{
			Log::WriteToOutput(Log::LogLevel::ERROR, _name.data(), fmt, _indentLevel);
		}
	};
}

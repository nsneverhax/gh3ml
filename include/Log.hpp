#pragma once

#ifdef ERROR
#undef ERROR
#endif // ERROR

namespace gh3ml
{
	enum class LogLevel
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR
	};

	class Log
	{
	private:
		static LogLevel s_currentLogLevel;

		static void AdjustConsoleBuffer(int16_t minLength);
		static bool RedirectConsoleIO();

		static void WriteToOutput(LogLevel level, const char* fmt, va_list argList);

	public:

		static LogLevel GetLogLevel();
		static void SetLogLevel(LogLevel level);

		static bool CreateConsole();
		static bool ReleaseConsole();


		static void Write(LogLevel level, const char* fmt, ...);
		static void Info(const char* fmt, ...);

		Log() = delete;
		~Log() = delete;
	};
}
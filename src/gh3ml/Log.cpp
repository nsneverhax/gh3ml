#include <cstdint>
#include <cstdarg>

#include <Log.hpp>

#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

// "Borrowed" from https://stackoverflow.com/questions/191842/how-do-i-get-console-output-in-c-with-a-windows-program

#undef ERROR

namespace gh3ml
{
	LogLevel Log::s_currentLogLevel = LogLevel::INFO;


    void Log::AdjustConsoleBuffer(int16_t minLength)
    {
        // Set the screen buffer to be big enough to scroll some text
        CONSOLE_SCREEN_BUFFER_INFO conInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
        if (conInfo.dwSize.Y < minLength)
            conInfo.dwSize.Y = minLength;
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
    }

    bool Log::RedirectConsoleIO()
    {
        bool result = true;
        FILE* fp;

        // Redirect STDIN if the console has an input handle
        if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
            if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
                result = false;
            else
                setvbuf(stdin, NULL, _IONBF, 0);

        // Redirect STDOUT if the console has an output handle
        if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
            if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
                result = false;
            else
                setvbuf(stdout, NULL, _IONBF, 0);

        // Redirect STDERR if the console has an error handle
        if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
            if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
                result = false;
            else
                setvbuf(stderr, NULL, _IONBF, 0);

        // Make C++ standard streams point to console as well.
        std::ios::sync_with_stdio(true);

        // Clear the error state for each of the C++ standard streams.
        std::wcout.clear();
        std::cout.clear();
        std::wcerr.clear();
        std::cerr.clear();
        std::wcin.clear();
        std::cin.clear();

        return result;
    }

    void Log::WriteToOutput(LogLevel level, const char* fmt, va_list argList)
    {

    }

	LogLevel Log::GetLogLevel()
	{
		return s_currentLogLevel;
	}

	void Log::SetLogLevel(LogLevel level)
	{
		s_currentLogLevel;
	}
	
    bool Log::CreateConsole()
    {
        bool result = false;

        // Release any current console and redirect IO to NUL
        ReleaseConsole();

        // Attempt to create new console
        if (AllocConsole())
        {
            AdjustConsoleBuffer(1024);
            result = RedirectConsoleIO();
        }

        return result;
    }

	bool Log::ReleaseConsole()
	{
        bool result = true;
        FILE* fp;

        // Just to be safe, redirect standard IO to NUL before releasing.

        // Redirect STDIN to NUL
        if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
            result = false;
        else
            setvbuf(stdin, NULL, _IONBF, 0);

        // Redirect STDOUT to NUL
        if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
            result = false;
        else
            setvbuf(stdout, NULL, _IONBF, 0);

        // Redirect STDERR to NUL
        if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
            result = false;
        else
            setvbuf(stderr, NULL, _IONBF, 0);

        // Detach from console
        if (!FreeConsole())
            result = false;

        return result;
	}

    void Log::Write(LogLevel level, const char* fmt, ...)
    {
        if (level <= s_currentLogLevel)
            return;

        va_list args;
        va_start(fmt, args);
        switch (level)
        {
        case gh3ml::LogLevel::TRACE:
            std::cout << "TRACE | ";
            break;
        case gh3ml::LogLevel::DEBUG:
            std::cout << "DEBUG | ";
            break;
        case gh3ml::LogLevel::INFO:
            std::cout << "INFO  | ";
            break;
        case gh3ml::LogLevel::WARN:
            std::cout << "WARN  | ";
            break;
        case gh3ml::LogLevel::ERROR:
        default:
            std::cout << "ERROR | ";
            break;
        }
        vprintf(fmt, args);
        std::cout << std::endl;
        va_end(args);
    }

    void Log::Trace(const char* fmt, ...)
    {
        if (LogLevel::TRACE <= s_currentLogLevel)
            return;

        va_list args;
        va_start(args, fmt);

        std::cout << "TRACE | ";

        vprintf(fmt, args);

        std::cout << std::endl;

        va_end(args);
    }
    void Log::Debug(const char* fmt, ...)
    {
        if (LogLevel::DEBUG <= s_currentLogLevel)
            return;

        va_list args;
        va_start(args, fmt);

        std::cout << "DEBUG | ";

        vprintf(fmt, args);

        std::cout << std::endl;

        va_end(args);
    }
    void Log::Info(const char* fmt, ...)
    {
        if (LogLevel::INFO <= s_currentLogLevel)
            return;

        va_list args;
        va_start(args, fmt);

        std::cout << "INFO  | ";

        vprintf(fmt, args);

        std::cout << std::endl;

        va_end(args);
    }
    void Log::Warn(const char* fmt, ...)
    {
        if (LogLevel::WARN <= s_currentLogLevel)
            return;

        va_list args;
        va_start(args, fmt);

        std::cout << "WARN  | ";

        vprintf(fmt, args);

        std::cout << std::endl;

        va_end(args);
    }
    void Log::Error(const char* fmt, ...)
    {
        if (LogLevel::ERROR <= s_currentLogLevel)
            return;

        va_list args;
        va_start(args, fmt);

        std::cout << "ERROR | ";

        vprintf(fmt, args);

        std::cout << std::endl;

        va_end(args);
    }
}
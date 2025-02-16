#include <cstdint>
#include <cstdarg>

#include <Nylon/Log.hpp>
#include "LogFile.hpp"

#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

// "Borrowed" from https://stackoverflow.com/questions/191842/how-do-i-get-console-output-in-c-with-a-windows-program

#undef ERROR

nylon::Log::LogLevel _currentLogLevel = nylon::Log::LogLevel::INFO;


void nylon::Log::AdjustConsoleBuffer(int16_t minLength)
{
    // Set the screen buffer to be big enough to scroll some text
    CONSOLE_SCREEN_BUFFER_INFO conInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
    if (conInfo.dwSize.Y < minLength)
        conInfo.dwSize.Y = minLength;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
}

bool nylon::Log::RedirectConsoleIO()
{
    bool result = true;
    FILE* fp;

    // Redirect STDIN if the console has an input handle
    if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONIN$", "r", stdin) != NULL)
            result = false;
        else
            setvbuf(stdin, NULL, _IONBF, NULL);

    // Redirect STDOUT if the console has an output handle
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stdout) != NULL)
            result = false;
        else
            setvbuf(stdout, NULL, _IONBF, NULL);

    // Redirect STDERR if the console has an error handle
    if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stderr) != NULL)
            result = false;
        else
            setvbuf(stderr, NULL, _IONBF, NULL);

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



nylon::Log::LogLevel nylon::Log::GetLogLevel()
{
    return _currentLogLevel;
}

void nylon::Log::SetLogLevel(LogLevel level)
{
    _currentLogLevel = level;
}
	
bool nylon::Log::CreateConsole()
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

bool nylon::Log::ReleaseConsole()
{
    bool result = true;
    FILE* fp;

    // Just to be safe, redirect standard IO to NUL before releasing.

    // Redirect STDIN to NUL
    if (freopen_s(&fp, "NUL:", "r", stdin) != NULL)
        result = false;
    else
        setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT to NUL
    if (freopen_s(&fp, "NUL:", "w", stdout) != NULL)
        result = false;
    else
        setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR to NUL
    if (freopen_s(&fp, "NUL:", "w", stderr) != NULL)
        result = false;
    else
        setvbuf(stderr, NULL, _IONBF, NULL);

    // Detach from console
    if (!FreeConsole())
        result = false;

    return result;
}

void nylon::Log::WriteToOutput(LogLevel level, const char* sourceName, const char* message)
{
    if (level < GetLogLevel())
        return;

    const auto now = std::chrono::system_clock::now();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int consoleColorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    char levelStr[6];
    switch (level)
    {
    case nylon::Log::LogLevel::TRACE:
        consoleColorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        strncpy(levelStr, "TRACE", sizeof(levelStr) - 1);
        break;
    case nylon::Log::LogLevel::DEBUG:
        consoleColorAttribute = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        strncpy(levelStr, "DEBUG", sizeof(levelStr) - 1);
        break;
    case nylon::Log::LogLevel::INFO:
        strncpy(levelStr, "INFO ", sizeof(levelStr) - 1);
        break;
    case nylon::Log::LogLevel::WARN:
        consoleColorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        strncpy(levelStr, "WARN ", sizeof(levelStr) - 1);
        break;
    case nylon::Log::LogLevel::ERROR:
    default:
        consoleColorAttribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED;
        strncpy(levelStr, "ERROR", sizeof(levelStr) - 1);
        break;
    }
    levelStr[5] = '\0';

    SetConsoleTextAttribute(hConsole, consoleColorAttribute);

    std::string prefix = std::format("{:%H:%M:%OS} {} [{}]: ", now, levelStr, sourceName);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    //std::string str = std::vformat(fmt, std::make_format_args(args...));

    std::cout << prefix << message << std::endl;
}
#include <Nylon/LogSource.hpp>
#include <Nylon/Log.hpp>

#include <string>
#include <format>

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



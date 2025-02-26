#pragma once

#include <cstdint>

namespace nylon
{
	/// <summary>
	/// Structure representing a point in time, used because WINE doesn't properly implement some time functions
	/// </summary>
	struct TimePoint
	{
		TimePoint()
		{

		}
		TimePoint(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second)
		{
			Year = year;
			Month = month;
			Day = day;

			Hour = hour;
			Minute = minute;
			Second = second;
		}

		uint16_t Year = 0; // V: might be a problem in the year 65535...
		uint8_t Month = 0;
		uint8_t Day = 0;

		uint8_t Hour = 0;
		uint8_t Minute = 0;
		uint8_t Second = 0;

		static TimePoint LocalNow()
		{
			std::time_t now = std::time(0);
			std::tm* now_tm = std::localtime(&now);

			return TimePoint(now_tm->tm_year + 1900, now_tm->tm_mon, now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
		}

		static TimePoint UtcNow()
		{
			std::time_t now = std::time(0);
			std::tm* now_tm = std::gmtime(&now);

			return TimePoint(now_tm->tm_year + 1900, now_tm->tm_mon, now_tm->tm_mday, now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
		}
	};
}
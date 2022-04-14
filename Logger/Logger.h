#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <stdio.h>      
#include <time.h>
#include <fstream>

#ifdef LOGGER_EXPORTS 
#define LOGGER_API _declspec(dllexport)
#else
#define LOGGER_API _declspec(dllimport)
#endif

class LOGGER_API Logger {
	//3 nivele de warning info, warning, error
public:
	enum class Level {
		Info,
		Warning,
		Error
	};

public:
	Logger(std::ostream& out, Level levelValue = Level::Info); //default este Info daca nu pun nici un parametru
	template<class ... Args>
	void Log(Level messageLevel, Args&& ... params) const;

private:
	Level m_minimLevel;
	std::ostream& m_out;
};

template <class ... Args>
inline void Logger::Log(Level messageLevel, Args&& ... paramx) const {
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int month = 1 + newtime.tm_mon;
	int day = newtime.tm_mday;
	int year = 1900 + newtime.tm_year;
	int hour = newtime.tm_hour;
	int minute = newtime.tm_min;
	int second = newtime.tm_sec;
	m_out << "[" << year << "/" << month << "/" << day << "] [" << hour << ":" << minute << ":" << second << "] ";
	if (messageLevel == Level::Info)
		m_out << "[Info] ";
	else if (messageLevel == Level::Warning)
		m_out << "[Warning] ";
	else if (messageLevel == Level::Error)
		m_out << "[Error] ";

	((m_out << std::forward<Args>(paramx)), ...);
	m_out << "\n";

}

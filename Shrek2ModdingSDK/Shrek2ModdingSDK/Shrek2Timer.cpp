/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

void Shrek2Timer::Start()
{
	try {
		if (IsRunning) return;
		IsRunning = true;
		timer.start();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::Start", ex.what());
	}
}

void Shrek2Timer::Stop()
{
	try {
		if (!IsRunning) return;
		IsRunning = false;
		timer.stop();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::Stop", ex.what());
	}
}

void Shrek2Timer::Reset()
{
	try {
		IsRunning = false;
		timer.reset();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::Reset", ex.what());
	}
}

bool Shrek2Timer::IsTimerRunning()
{
	return IsRunning;
}

std::string Shrek2Timer::GetTimeString()
{
	try {
		int mils = CurrentMilliseconds();
		int secs = CurrentSeconds();
		int mins = CurrentMinutes();

		std::string milliseconds = (mils <= 9 ? "00" : (mils <= 99 ? "0" : "")) + std::to_string(mils);
		std::string seconds = (secs <= 9 ? "0" : "") + std::to_string(secs);
		std::string minutes = (mins <= 9 ? "0" : "") + std::to_string(mins);

		return minutes + ":" + seconds + "." + milliseconds;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::GetTimeString", ex.what());
		return "";
	}
}

int Shrek2Timer::TotalMilliseconds()
{
	try {
		return timer.count<std::chrono::milliseconds>();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::TotalMilliseconds", ex.what());
		return 0;
	}
}

int Shrek2Timer::TotalSeconds()
{
	try {
		return TotalMilliseconds() / 1000.0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::TotalSeconds", ex.what());
		return 0;
	}
}

int Shrek2Timer::TotalMinutes()
{
	try {
		return TotalSeconds() / 60;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::TotalMinutes", ex.what());
		return 0;
	}
}

int Shrek2Timer::CurrentMilliseconds()
{
	try {
		return (int)TotalMilliseconds() % 1000;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::CurrentMilliseconds", ex.what());
		return 0;
	}
}

int Shrek2Timer::CurrentSeconds()
{
	try {
		return (int)TotalSeconds() % 60;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::CurrentSeconds", ex.what());
		return 0;
	}
}

int Shrek2Timer::CurrentMinutes()
{
	try {
		return (int)TotalMinutes() % 60;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Timer::CurrentMinutes", ex.what());
		return 0;
	}
}
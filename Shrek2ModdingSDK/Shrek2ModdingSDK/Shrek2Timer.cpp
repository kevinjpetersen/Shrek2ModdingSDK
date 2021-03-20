#include "Shrek2ModdingSDK.h"

void Shrek2Timer::Start()
{
	if (IsRunning) return;
	IsRunning = true;
	timer.start();
}

void Shrek2Timer::Stop()
{
	if (!IsRunning) return;
	IsRunning = false;
	timer.stop();
}

void Shrek2Timer::Reset()
{
	IsRunning = false;
	timer.reset();
}

bool Shrek2Timer::IsTimerRunning()
{
	return IsRunning;
}

std::string Shrek2Timer::GetTimeString()
{
	int mils = CurrentMilliseconds();
	int secs = CurrentSeconds();
	int mins = CurrentMinutes();

	std::string milliseconds = (mils <= 9 ? "0" : "") + std::to_string(mils);
	std::string seconds = (secs <= 9 ? "0" : "") + std::to_string(secs);
	std::string minutes = (mins <= 9 ? "0" : "") + std::to_string(mins);

	return minutes + ":" + seconds + "." + milliseconds;
}

int Shrek2Timer::TotalMilliseconds()
{
	return timer.count<std::chrono::milliseconds>();
}

int Shrek2Timer::TotalSeconds()
{
	return TotalMilliseconds() / 1000.0;
}

int Shrek2Timer::TotalMinutes()
{
	return TotalSeconds() / 60;
}

int Shrek2Timer::CurrentMilliseconds()
{
	return (int)TotalMilliseconds() % 1000;
}

int Shrek2Timer::CurrentSeconds()
{
	return (int)TotalSeconds() % 60;
}

int Shrek2Timer::CurrentMinutes()
{
	return (int)TotalMinutes() % 60;
}
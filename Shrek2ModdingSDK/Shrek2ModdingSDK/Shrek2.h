/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#pragma once
class Shrek2
{
public:
	inline static Shrek2* Instance;

	Shrek2() {
		if (!Instance) Instance = this;
	}

	void InitializeEvents();
	void Initialize(std::string ModName, bool ShowConsoleByDefault);
	void ShowConsole();
	void HideConsole();
	bool IsConsoleVisible();
	void LogToConsole(std::string logMessage);
	LONG GetGameWindowHeight();
	LONG GetGameWindowWidth();
	LONG GetGameClientHeight();
	LONG GetGameClientWidth();
	Shrek2Pointers Variables;
	Shrek2Functions Functions;
	Shrek2Events Events = Shrek2Events();
	Shrek2Sound Sounds;
	Shrek2Input Input = Shrek2Input();
	Shrek2Triggers Triggers = Shrek2Triggers();
	Shrek2Config Config;
	Shrek2Storage Storage;
	Shrek2EntityList Entities = Shrek2EntityList();
	bool IsModRunning;
	void SetDllHandle(HMODULE hModule);
	task<void> Delay(unsigned int delayAmountInMs);
	void Wait(unsigned int waitAmountInMs);
	RECT GameWindowSize;
	RECT GameClientSize;
private:
	bool IsMinimized = false;
	bool IsFullscreen = false;
	bool AddConsole;
	HMODULE DllHandle;
	HWND WindowHandle;
	std::string DllName;
	std::string DllPath;
};


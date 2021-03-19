#pragma once
class Shrek2
{
public:
	void InitializeEvents();
	void Initialize(std::string ModName);
	void ShowConsole();
	void HideConsole();
	bool IsConsoleVisible();
	void LogToConsole(std::string logMessage);
	LONG GetGameWindowHeight();
	LONG GetGameWindowWidth();
	Shrek2Pointers Variables;
	Shrek2Functions Functions;
	Shrek2Events Events = Shrek2Events();
	Shrek2Sound Sounds;
	Shrek2Input Input;
	Shrek2Triggers Triggers = Shrek2Triggers();
	bool IsModRunning;
	void SetDllHandle(HMODULE hModule);
	task<void> Delay(unsigned int delayAmountInMs);
	void Wait(unsigned int waitAmountInMs);
	RECT GameWindowSize;
private:
	bool AddConsole;
	HMODULE DllHandle;
	HWND WindowHandle;
	std::string DllName;
	std::string DllPath;
};


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
	Shrek2Pointers Variables;
	Shrek2Functions Functions;
	Shrek2Events Events = Shrek2Events();
	bool IsModRunning;
	void SetDllHandle(HMODULE hModule);
private:
	bool AddConsole;
	HMODULE DllHandle;
	HWND WindowHandle;
	std::string DllName;
};


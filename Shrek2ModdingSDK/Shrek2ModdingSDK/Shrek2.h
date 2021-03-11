#pragma once
class Shrek2
{
public:
	void Initialize(std::string ModName);
	void ShowConsole();
	void HideConsole();
	bool IsConsoleVisible();
	void LogToConsole(std::string logMessage);
	Shrek2Pointers Variables;
	Shrek2Functions Functions;
	Shrek2Events Events;
	bool IsModRunning;
	void SetDllHandle(HMODULE hModule);
private:
	bool AddConsole;
	HMODULE DllHandle;
	HWND WindowHandle;
	std::string DllName;
};


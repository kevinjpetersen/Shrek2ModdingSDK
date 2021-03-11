#pragma once
class Shrek2
{
public:
	void Initialize(void (*OnStart)(), void (*OnTick)(), std::string ModName, std::string GameWindowName);
	void OpenLevel(std::string levelName);
	void ShowConsole();
	void HideConsole();
	bool IsConsoleVisible();
	void LogToConsole(std::string logMessage);
	Shrek2Pointers Variables;
	bool IsModRunning;
	void SetDllHandle(HMODULE hModule);
private:
	void (*OnStart)();
	void (*OnTick)();
	bool AddConsole;
	HMODULE DllHandle;
	HWND WindowHandle;
	std::string DllName;
};


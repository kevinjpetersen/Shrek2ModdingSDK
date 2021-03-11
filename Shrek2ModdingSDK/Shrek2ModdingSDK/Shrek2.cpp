#include "Shrek2ModdingSDK.h"

void Shrek2::Initialize(HMODULE DllHandle, void (*OnStart)(), void (*OnTick)(), std::string ModName, std::string GameWindowName = "Shrek 2")
{
	Shrek2::DllHandle = DllHandle;
	Shrek2::OnStart = OnStart;
	Shrek2::OnTick = OnTick;
	Shrek2::AddConsole = AddConsole;

	IsModRunning = true;
	Variables = Shrek2Pointers();

	Shrek2::WindowHandle = FindWindowA(NULL, GameWindowName.c_str());

	bool findWindow = true;
	while (findWindow) {
		HWND wnd = FindWindowA(NULL, GameWindowName.c_str());
		if (wnd) {
			Shrek2::WindowHandle = wnd;
			findWindow = false;
			break;
		}

		if (!IsModRunning) return;
		Sleep(500);
	}

	LogToConsole("Mod '" + ModName + "' loaded.");

	OnStart();
	while (IsModRunning) {
		Sleep(1);

		if (Shrek2::WindowHandle != GetForegroundWindow()) {
			continue;
		}

		OnTick();
	}

	LogToConsole("Mod '" + ModName + "' unloaded.");
	return;
}

void Shrek2::LogToConsole(std::string logMessage)
{
	std::cout << logMessage << std::endl;
}

void Shrek2::HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void Shrek2::ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool Shrek2::IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}


void Shrek2::OpenLevel(std::string levelName)
{
	// TBD
}



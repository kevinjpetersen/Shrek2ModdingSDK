#include "Shrek2ModdingSDK.h"

void Shrek2::Initialize(std::string ModName)
{
	Shrek2::AddConsole = AddConsole;

	char dllPath[MAX_PATH];
	GetModuleFileName(DllHandle, dllPath, MAX_PATH);

	DllName = fs::path(dllPath).stem().u8string();

	IsModRunning = true;
	Variables = Shrek2Pointers();
	Functions = Shrek2Functions(DllName);

	LogToConsole("DllName is: " + DllName);

	Shrek2::WindowHandle = FindWindowA(NULL, "Shrek 2");

	bool findWindow = true;
	while (findWindow) {
		HWND wnd = FindWindowA(NULL, "Shrek 2");
		if (wnd) {
			Shrek2::WindowHandle = wnd;
			findWindow = false;
			break;
		}

		if (!IsModRunning) return;
		Sleep(500);
	}

	LogToConsole("Mod '" + ModName + "' loaded.");

	if(Events.OnStart) Events.OnStart();
	while (IsModRunning) {
		Sleep(1);

		if (Shrek2::WindowHandle != GetForegroundWindow()) {
			continue;
		}

		Events.EventUpdates();
		if(Events.OnTick) Events.OnTick();
	}

	LogToConsole("Mod '" + ModName + "' unloaded.");
	return;
}

void Shrek2::LogToConsole(std::string logMessage)
{
	std::cout << logMessage << std::endl;
}

void Shrek2::SetDllHandle(HMODULE hModule)
{
	DllHandle = hModule;
}

task<void> Shrek2::Delay(unsigned int delayAmountInMs)
{
	task_completion_event<void> tce;
	auto fire_once = new timer<int>(delayAmountInMs, 0, nullptr, false);

	auto callback = new call<int>([tce](int)
		{
			tce.set();
		});

	fire_once->link_target(callback);
	fire_once->start();

	task<void> event_set(tce);

	return event_set.then([callback, fire_once]()
		{
			delete callback;
			delete fire_once;
		});
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


/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

DWORD WINAPI CutLogThread(HINSTANCE hModule)
{
	Shrek2& Game = *Shrek2::Instance;

	while (Game.IsModRunning) {
		Sleep(1000 / Game.OnCutLogTPS);
		Game.Events.EU_OnCutLogTick();
	}

	ExitThread(0);
}

DWORD WINAPI ActorListThread(HINSTANCE hModule)
{
	Shrek2& Game = *Shrek2::Instance;

	while (Game.IsModRunning) {
		Sleep(1000 / Game.OnActorListTPS);
		if(Game.Events.OnActorList) Game.Events.OnActorList();
	}

	ExitThread(0);
}


void Shrek2::Initialize(std::string ModName, bool ShowConsoleByDefault = true)
{
	Shrek2::AddConsole = ShowConsoleByDefault;
	if (ShowConsoleByDefault)
	{
		ShowConsole();
	}
	else {
		HideConsole();
	}

	char dllPath[MAX_PATH];
	GetModuleFileName(DllHandle, dllPath, MAX_PATH);

	auto path = fs::path(dllPath);

	DllName = path.stem().u8string();
	DllPath = path.u8string();
	Shrek2StaticVars::DllFolderPath = path.parent_path().u8string();

	IsModRunning = true;
	Sounds = Shrek2Sound(Shrek2StaticVars::DllFolderPath);
	Variables = Shrek2Pointers();
	Functions = Shrek2Functions(DllName);
	Config = Shrek2Config(Shrek2StaticVars::DllFolderPath);
	Storage = Shrek2Storage(Shrek2StaticVars::DllFolderPath);
	Input.DllPath = Shrek2StaticVars::DllFolderPath;
	Input.LoadBinds();

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

	GameWindowSize = Shrek2Utils::GetWindowSize(WindowHandle);

	LogToConsole("Mod '" + ModName + "' loaded.");

	bool tempIsMinimized = false;
	QUERY_USER_NOTIFICATION_STATE pquns;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CutLogThread, NULL, 0, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ActorListThread, NULL, 0, NULL);

	if (Events.OnStart) Events.OnStart();
	while (IsModRunning) {
		Sleep(1000 / OnTickTPS);

		GameWindowSize = Shrek2Utils::GetWindowSize(WindowHandle);
		GameClientSize = Shrek2Utils::GetClientSize(WindowHandle);
		Shrek2UI::GameWindowSize = GameWindowSize;

		tempIsMinimized = IsIconic(WindowHandle);

		SHQueryUserNotificationState(&pquns);
		if (pquns == QUNS_BUSY && !IsFullscreen)
		{
			IsFullscreen = true;
			Shrek2UI::TriggerReset();
		}
		else if (pquns != QUNS_BUSY && IsFullscreen)
		{
			IsFullscreen = false;
			Shrek2UI::TriggerReset();
		}

		if (tempIsMinimized && !IsMinimized) {
			IsMinimized = true;
		}
		else if (!tempIsMinimized && IsMinimized)
		{
			IsMinimized = false;
			Shrek2UI::TriggerReset();
		}

		if (Shrek2::WindowHandle != GetForegroundWindow()) {
			continue;
		}
		
		if (Triggers.EnableTriggers)
		{
			Shrek2Maps map = Shrek2Utils::MapStringToMap(Variables.GetCurrentMap());

			float x = Variables.GetPositionX();
			float y = Variables.GetPositionY();
			float z = Variables.GetPositionZ();

			float colHeight = Variables.GetCollisionHeight();
			float colRadius = Variables.GetCollisionRadius();

			Triggers.CheckTriggers(Shrek2Vector3(x, y, z), map, Shrek2Vector3(colRadius, colRadius, colHeight));
		}
		Events.EventUpdates();
		if (Events.OnTick) Events.OnTick();
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

LONG Shrek2::GetGameClientHeight()
{
	return GameClientSize.bottom - GameClientSize.top;
}

LONG Shrek2::GetGameClientWidth()
{
	return GameClientSize.right - GameClientSize.left;
}

void Shrek2::Wait(unsigned int waitAmountInMs)
{
	concurrency::wait(1000);
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

LONG Shrek2::GetGameWindowHeight()
{
	return GameWindowSize.bottom - GameWindowSize.top;
}

LONG Shrek2::GetGameWindowWidth()
{
	return GameWindowSize.right - GameWindowSize.left;
}
/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

DWORD WINAPI CutLogThread(HINSTANCE hModule)
{
	try {
		Shrek2& Game = *Shrek2::Instance;

		while (Game.IsModRunning) {
			try {
				Sleep(1000 / Game.OnCutLogTPS);
				Game.Events.EU_OnCutLogTick();
			}
			catch (std::exception& ex)
			{
				Shrek2Logging::LogError("Shrek2::CutLogThread::Inner", ex.what());
				Sleep(100);
			}
		}

		ExitThread(0);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::CutLogThread::Outer", ex.what());
	}
}

DWORD WINAPI ActorListThread(HINSTANCE hModule)
{
	try {
		Shrek2& Game = *Shrek2::Instance;

		while (Game.IsModRunning) {
			try {
				Sleep(1000 / Game.OnActorListTPS);
				if (Game.Events.OnActorList) Game.Events.OnActorList();
			}
			catch (std::exception& ex)
			{
				Shrek2Logging::LogError("Shrek2::ActorListThread::Inner", ex.what());
				Sleep(100);
			}
		}

		ExitThread(0);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::ActorListThread::Outer", ex.what());
	}
}


void Shrek2::Initialize(std::string ModName, bool ShowConsoleByDefault = true)
{
	try {
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
			try {
				HWND wnd = FindWindowA(NULL, "Shrek 2");
				if (wnd) {
					Shrek2::WindowHandle = wnd;
					findWindow = false;
					break;
				}

				if (!IsModRunning) return;
				Sleep(500);
			}
			catch (std::exception& ex)
			{
				Shrek2Logging::LogError("Shrek2::Initialize::FindWindow", ex.what());
				Sleep(500);
			}
		}

		Input.WindowHandle = Shrek2::WindowHandle;
		Functions.WindowHandle = Shrek2::WindowHandle;
		GameWindowSize = Shrek2Utils::GetWindowSize(WindowHandle);

		LogToConsole("Mod '" + ModName + "' loaded.");

		bool tempIsMinimized = false;
		QUERY_USER_NOTIFICATION_STATE pquns;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CutLogThread, NULL, 0, NULL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ActorListThread, NULL, 0, NULL);

		IsGameFocused = true;

		if (Events.OnStart) Events.OnStart();
		while (IsModRunning) {
			try {
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
					if (IsGameFocused)
					{
						IsGameFocused = false;
						if (!PauseGameOnFocusLost) {
							LogToConsole("Game Paused");
						}
					}
				}
				else {
					if (!IsGameFocused) {
						IsGameFocused = true;
						if (!PauseGameOnFocusLost) {
							LogToConsole("Game Unpaused -- Setting PauseDelay to 32140800");
							Functions.CC("Set Engine.LevelInfo PauseDelay 32140800");
						}
					}
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
			catch (std::exception& ex)
			{
				Shrek2Logging::LogError("Shrek2::Initialize::MainLoop", ex.what());
				Sleep(100);
			}
		}

		LogToConsole("Mod '" + ModName + "' unloaded.");
		return;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::Initialize::Outer", ex.what());
	}
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

POINT Shrek2::GetMousePosition()
{
	try {
		POINT p = POINT();
		if (!WindowHandle) return p;

		if (GetCursorPos(&p))
		{
			if (ScreenToClient(WindowHandle, &p))
			{
				return p;
			}
		}
		return p;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::GetMousePosition", ex.what());
		return POINT();
	}
}

void Shrek2::Wait(unsigned int waitAmountInMs)
{
	concurrency::wait(1000);
}

task<void> Shrek2::Delay(unsigned int delayAmountInMs)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::Delay", ex.what());
		return task<void>();
	}
}

void Shrek2::MinimizeConsole()
{
	try {
		::ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::MinimizeConsole", ex.what());
	}
}

void Shrek2::HideConsole()
{
	try {
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::HideConsole", ex.what());
	}
}

void Shrek2::ShowConsole()
{
	try {
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::ShowConsole", ex.what());
	}
}

bool Shrek2::IsConsoleVisible()
{
	try {
		return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::IsConsoleVisible", ex.what());
	}
}

LONG Shrek2::GetGameWindowHeight()
{
	try {
		return GameWindowSize.bottom - GameWindowSize.top;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::GetGameWindowHeight", ex.what());
		return 0;
	}
}

LONG Shrek2::GetGameWindowWidth()
{
	try {
		return GameWindowSize.right - GameWindowSize.left;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2::GetGameWindowWidth", ex.what());
		return 0;
	}
}
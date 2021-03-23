/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"
#include <algorithm> 

Shrek2 Game = Shrek2();

Shrek2Timer timer1 = Shrek2Timer();

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		if (timer1.IsTimerRunning()) {
			timer1.Stop();
		}
		else {
			timer1.Start();
		}
	}
}

void RenderUI()
{
	Shrek2UI::RenderText(
		Shrek2Rect(10, Game.GetGameWindowHeight() / 2 - 90, 400, 100),
		"Timer: " + timer1.GetTimeString(),
		Shrek2UI::GetColorAlpha(255, 255, 255, 255),
		true
	);
}

void OnStart()
{
	Shrek2UI::GameWindowSize = Game.GameWindowSize;
	Shrek2UI::RenderUI = RenderUI;
	Shrek2UI::Initialize();
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;

	Game.Initialize("Shrek 2 Test Mod", false);

	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Game.SetDllHandle(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializationThread, NULL, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (Game.IsModRunning) {
			Game.IsModRunning = false;
			Shrek2UI::StopUI();
			Sleep(1000);
		}
		break;
	}
	return TRUE;
}
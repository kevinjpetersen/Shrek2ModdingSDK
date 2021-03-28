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

bool allowTiming = false;

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		Game.Triggers.OverwriteTrigger("Location1", Shrek2Trigger(Game.Variables.GetPosition(), Shrek2Vector3(100)));
	}

	if (Game.Input.OnKeyPress(Shrek2Input::H)) {
		Game.Triggers.OverwriteTrigger("Location2", Shrek2Trigger(Game.Variables.GetPosition(), Shrek2Vector3(100)));
	}

	if (Game.Input.OnKeyPress(Shrek2Input::J)) {
		allowTiming = !allowTiming;
		Game.LogToConsole("Allow timing: " + std::to_string(allowTiming));
	}
}

void OnTriggerEnter(std::string name, Shrek2Trigger trigger)
{
	Game.LogToConsole(name);

	if (Shrek2Utils::DoesEqual(name, "Location1")) {
		auto trigger = Game.Triggers.GetTrigger("Location2");
		
		if (!trigger.IsPositionZero()) {
			if (allowTiming) {
				if (timer1.IsTimerRunning()) {
					timer1.Stop();
				}
				else {
					timer1.Start();
				}
			}
		}
	}

	if (Shrek2Utils::DoesEqual(name, "Location2")) {
		auto trigger = Game.Triggers.GetTrigger("Location1");

		if (!trigger.IsPositionZero()) {
			if (allowTiming) {
				if (timer1.IsTimerRunning()) {
					timer1.Stop();
				}
				else {
					timer1.Start();
				}
			}
		}
	}
}

void RenderUI()
{
	Shrek2UI::RenderText(
		Shrek2Rect(10, Game.GetGameClientHeight() / 2 - 90, 400, 100),
		"Allow timing: " + std::to_string(allowTiming),
		Shrek2UI::GetColorAlpha(255, 255, 255, 255),
		true
	);

	Shrek2UI::RenderText(
		Shrek2Rect(10, Game.GetGameClientHeight() / 2 - 50, 400, 100),
		"Time: " + timer1.GetTimeString(),
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
	Game.Triggers.AddTrigger("Location1", Shrek2Trigger(Shrek2Vector3(0, 0, 0), Shrek2Vector3(100)));
	Game.Triggers.AddTrigger("Location2", Shrek2Trigger(Shrek2Vector3(0, 0, 0), Shrek2Vector3(100)));
	
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	Game.Triggers.OnTriggerEnter = OnTriggerEnter;

	Game.Initialize("Shrek 2 Test Mod", true);

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
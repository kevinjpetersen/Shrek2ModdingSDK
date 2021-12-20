/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

bool freecamOn = false;

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::H)) {
		Game.Variables.SetPlayerHealth(9999);
	}

	/*if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		freecamOn = !freecamOn;
		auto X = Game.Variables.GetCamPositionX();
		auto Y = Game.Variables.GetCamPositionY();
		auto Z = Game.Variables.GetCamPositionZ();

		auto rotX = Game.Variables.GetCamRotationX();
		auto rotY = Game.Variables.GetCamRotationY();
		auto rotZ = Game.Variables.GetCamRotationZ();

		if (freecamOn == false)
		{
			Game.Functions.CCS({
				"set shgame.version bdebugenabled true",
				"set kwgame.kwversion bdebugenabled true",
				"freecam",
				"slomo 1"
			});

			Game.Variables.SetPosition(Shrek2Vector3(X, Y, Z));

			Game.Variables.SetRotationX(rotX);
			Game.Variables.SetRotationY(rotY);
		}
		else {
			Game.Functions.CCS({
				"set shgame.version bdebugenabled true",
				"set kwgame.kwversion bdebugenabled true",
				"freecam",
				"slomo 2"
			});
		}
	}*/
}

void RenderUI()
{

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

	Game.Initialize("Shrek 2 Health Mod", false);

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
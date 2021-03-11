#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();

void OnStart()
{
}

bool IsInWater = false;

void OnTick()
{
	if (Game.Variables.GetIsInWater()) {
		if (IsInWater) return;
		IsInWater = true;

		Game.Functions.OpenMap(Shrek2Maps::The_Hunt_Part2);

		/*Game.Functions.CCS({
			"sethealth 50",
			"addcoins 50"
		});*/
	}
	else 
	{
		IsInWater = false;
	}
}


DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Initialize(OnStart, OnTick, "Shrek 2 Test Mod");
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
			Sleep(1000);
		}
		break;
	}
	return TRUE;
}
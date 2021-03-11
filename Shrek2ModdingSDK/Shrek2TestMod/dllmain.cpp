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

		float localPlayerPosZ = Game.Variables.GetPositionZ();
		localPlayerPosZ = localPlayerPosZ + 200;
		Game.Variables.SetPositionZ(localPlayerPosZ);
		Game.Variables.SetVelocityZ(0);
		Game.LogToConsole("Water");
	}
	else 
	{
		IsInWater = false;
	}
}


DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Initialize(hModule, OnStart, OnTick, "Shrek 2 Test Mod", "Shrek 2");
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
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
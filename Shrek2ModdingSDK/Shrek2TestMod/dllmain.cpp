#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();

void OnStart()
{
}

void OnPlayerInWaterEnter()
{
	Game.LogToConsole("Enter Water");
	Game.Variables.SetPlayerHealth(Game.Variables.GetPlayerHealth() - 5);
}

void OnPlayerInWaterTick() 
{
	Game.LogToConsole("Tick Water");
}

void OnPlayerInWaterExit()
{
	Game.LogToConsole("Exit Water");
}

void OnPlayerHealthUpdate(float oldHealth, float newHealth)
{
	Game.LogToConsole(
		"Old Health: " + std::to_string(oldHealth) + 
		" | New Health: " + std::to_string(newHealth) + 
		" | Change: " + std::to_string(abs(newHealth - oldHealth))
	);
}

void OnPlayerInAirEnter()
{
	Game.LogToConsole("In Air Enter");
}

void OnPlayerLand()
{
	Game.LogToConsole("Player Landed");
}

void OnTick()
{
	
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	Game.Events.OnPlayerInWaterEnter = OnPlayerInWaterEnter;
	//Game.Events.OnPlayerInWaterTick = OnPlayerInWaterTick;
	Game.Events.OnPlayerInWaterExit = OnPlayerInWaterExit;
	Game.Events.OnPlayerHealthUpdate = OnPlayerHealthUpdate;
	Game.Events.OnPlayerInAirEnter = OnPlayerInAirEnter;
	Game.Events.OnPlayerLand = OnPlayerLand;

	Game.Initialize("Shrek 2 Test Mod");
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
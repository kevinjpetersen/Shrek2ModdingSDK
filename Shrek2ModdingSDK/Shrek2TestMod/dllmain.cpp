#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();

bool isBackflipping = false;
int rotation = 0;
bool isBack = true;

void OnStart()
{
}

void OnPlayerInWaterEnter()
{
	Game.Functions.CCS({
   "mortifyplayer",
   "adminsay Blablablabla"
		});

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
	//Game.Variables.SetGameSpeed(0.5f);
	isBackflipping = true;
	isBack = (rand() % 100 + 1) >= 50;
	rotation = isBack ? 0 : 65000;
	//Game.Variables.SetVisualScaleY(1.5f);
}

void OnPlayerInAirTick()
{
	Game.LogToConsole("In Air Tick");
}

void OnPlayerLand()
{
	Game.Variables.SetGodMode(true);
	Game.LogToConsole("Player Landed");
	//Game.Variables.SetGameSpeed(1);
	Game.Variables.SetRotationX(0);
	isBackflipping = false;
	//Game.Variables.SetVisualScaleY(1);
	
}

void OnPlayerHitJumpMagnetHit()
{
	Game.LogToConsole("Hit Jump Magnet (Auto Jump)");
}

void OnPlayerHitJumpMagnetDone()
{
	Game.LogToConsole("Landed Jump Magnet (Auto Jump)");
}

void OnPlayerHitBouncePadHit()
{
	Game.LogToConsole("Hit Bounce Pad");
}

void OnPlayerHitBouncePadDone()
{
	Game.LogToConsole("Landed Bounce Pad");
}

void OnPlayerDie()
{
	Game.LogToConsole("Player Died");
}

void OnPlayerRespawn()
{
	Game.LogToConsole("Player Respawned");
}

void OnPlayerMove(float x, float y, float z)
{
	Game.LogToConsole("Player Move | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Z: " + std::to_string(z));
}

void OnPlayerRotate(float x, float y, float z)
{
	Game.LogToConsole("Player Rotate | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Z: " + std::to_string(z));
}

void OnTick()
{
	Game.Variables.SetDoubleJumpHeight(1000);
	Game.Variables.SetJumpHeight(1000);

	if (isBackflipping) {
		if (isBack) {
			rotation += 50;
			if (rotation >= 65000) {
				// Finished backclip
				rotation = 0;
				isBackflipping = false;
			}
		}
		else {
			rotation -= 50;
			if (rotation <= 500) {
				// Finished frontclip
				rotation = 0;
				isBackflipping = false;
			}
		}
		Game.Variables.SetRotationX(rotation);
	}
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	Game.Events.OnPlayerInWaterEnter = OnPlayerInWaterEnter;
	//Game.Events.OnPlayerInWaterTick = OnPlayerInWaterTick;
	//Game.Events.OnPlayerInWaterExit = OnPlayerInWaterExit;
	//Game.Events.OnPlayerHealthUpdate = OnPlayerHealthUpdate;
	Game.Events.OnPlayerInAirEnter = OnPlayerInAirEnter;
	//Game.Events.OnPlayerInAirTick = OnPlayerInAirTick;
	Game.Events.OnPlayerLand = OnPlayerLand;
	//Game.Events.OnPlayerHitJumpMagnetHit = OnPlayerHitJumpMagnetHit;
	//Game.Events.OnPlayerHitJumpMagnetDone = OnPlayerHitJumpMagnetDone;
	//Game.Events.OnPlayerHitBouncePadHit = OnPlayerHitBouncePadHit;
	//Game.Events.OnPlayerHitBouncePadDone = OnPlayerHitBouncePadDone;
	//Game.Events.OnPlayerDie = OnPlayerDie;
	//Game.Events.OnPlayerRespawn = OnPlayerRespawn;
	//Game.Events.OnPlayerMove = OnPlayerMove;
	//Game.Events.OnPlayerRotate = OnPlayerRotate;

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
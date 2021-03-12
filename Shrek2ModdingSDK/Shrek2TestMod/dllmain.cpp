#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();

bool isBackflipping = false;
int flipRotation = 0;
bool isBack = true;

bool isDiving = false;
int swimRotation = 0;
int defaultRotRateX = 4096;


bool bIsInAir = false;
float BhopVelX = 0;
float BhopVelY = 0;
float BhopMultipier = 0.7;

void OnStart()
{
}

void OnPlayerInWaterEnter()
{
	isDiving = true;
	swimRotation = 0;
	Game.Variables.SetRotationRateX(0);
	Game.Variables.SetPrePivotZ(-20);

	Game.Variables.SetWaterSpeed(700);
	Game.Variables.SetWaterSpeed2(700);
}

void OnPlayerInWaterTick()
{
	if (swimRotation > -15000) {
		swimRotation -= 70;
		Game.Variables.SetRotationX(swimRotation);
	}
}

void OnPlayerInWaterExit()
{
	isDiving = false;
	swimRotation = 0;
	Game.Variables.SetPrePivotZ(0);
	Game.Variables.SetRotationRateX(20000);
}

void OnPlayerHealthUpdate(float oldHealth, float newHealth)
{
	/*Game.LogToConsole(
		"Old Health: " + std::to_string(oldHealth) +
		" | New Health: " + std::to_string(newHealth) +
		" | Change: " + std::to_string(abs(newHealth - oldHealth))
	);*/
}

void OnPlayerInAirEnter()
{
	/*isBackflipping = true;
	isBack = (rand() % 100 + 1) >= 50;
	flipRotation = isBack ? 0 : 65000;*/

	Game.LogToConsole("Air");
	bIsInAir = true;
}

void OnPlayerInAirTick()
{
	BhopVelX = Game.Variables.GetVelocityX();
	BhopVelY = Game.Variables.GetVelocityY();

	Game.LogToConsole("Hello");

	//if (isBackflipping) {
	//	if (isBack) {
	//		flipRotation += 50;
	//		if (flipRotation >= 65000) {
	//			// Finished backclip
	//			flipRotation = 0;
	//			isBackflipping = false;
	//		}
	//	}
	//	else {
	//		flipRotation -= 50;
	//		if (flipRotation <= 500) {
	//			// Finished frontclip
	//			flipRotation = 0;
	//			isBackflipping = false;
	//		}
	//	}
	//	Game.Variables.SetRotationX(flipRotation);
	//}
}

void OnPlayerLand()
{
	Game.LogToConsole("Land");
	bIsInAir = false;

	Game.Delay(500).then([]
	{
		if (bIsInAir == true)
		{
			Game.Variables.SetVelocityX(BhopVelX);
			Game.Variables.SetVelocityY(BhopVelY);
			Game.LogToConsole("Player bhopped!");
		}
		else
		{
			Game.LogToConsole("Player failed to bhop!");
		}
	});
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
	/*Game.Variables.SetDoubleJumpHeight(1000);
	Game.Variables.SetJumpHeight(1000);*/
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	//Game.Events.OnPlayerInWaterEnter = OnPlayerInWaterEnter;
	//Game.Events.OnPlayerInWaterTick = OnPlayerInWaterTick;
	//Game.Events.OnPlayerInWaterExit = OnPlayerInWaterExit;
	//Game.Events.OnPlayerHealthUpdate = OnPlayerHealthUpdate;
	Game.Events.OnPlayerInAirEnter = OnPlayerInAirEnter;
	Game.Events.OnPlayerInAirTick = OnPlayerInAirTick;
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
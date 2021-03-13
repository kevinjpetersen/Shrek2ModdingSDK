#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();
void OnStart()
{
}

void OnPlayerHitBouncePadHit() {
    Game.LogToConsole("BOUNCE PAD HIT");
}

bool bIsInAir = false;
bool bApplyingVel = false;
bool bFinishedUpdatingVel = false;
float BhopVelX = 0;
float BhopVelY = 0;
float BhopMultiplier = 5.5;
int currentMs = 0;

void OnTick()
{
    /*if (bIsInAir == true)
    {
        currentMs += 1;
        if (currentMs >= 15) {
            currentMs = 0;
            Game.LogToConsole("X: " + std::to_string(BhopVelX));
            Game.LogToConsole("Y: " + std::to_string(BhopVelY));
        }
    }*/
}

void OnPlayerLand()
{
    Game.LogToConsole("ON LAND");
    /*Game.Variables.SetVelocityX(0);
    Game.Variables.SetVelocityY(0);

    bIsInAir = false;
    bFinishedUpdatingVel = true;
    bApplyingVel = true;

    

    Game.Delay(100).then([]
        {
            if (bIsInAir == true && bFinishedUpdatingVel == false)
            {
                Game.Variables.SetVelocityX(BhopVelX * BhopMultiplier);
                Game.Variables.SetVelocityY(BhopVelY * BhopMultiplier);
                Game.LogToConsole("DONE X: " + std::to_string(BhopVelX));
                Game.LogToConsole("DONE Y: " + std::to_string(BhopVelY));
                Game.LogToConsole("Player bhopped!");
                bFinishedUpdatingVel = true;
                bApplyingVel = false;
            }
            else
            {
                Game.LogToConsole("Player failed to bhop!");
                bApplyingVel = false;
            }
        });*/
}

void OnPlayerInAirEnter()
{
    Game.LogToConsole("ENTER AIR");
    /*bIsInAir = true;
    bFinishedUpdatingVel = false;*/
}

void OnPlayerInAirTick()
{
    if (bApplyingVel == false)
    {
        BhopVelX = Game.Variables.GetVelocityX();
        BhopVelY = Game.Variables.GetVelocityY();
    }
}

//bool isBackflipping = false;
//int flipRotation = 0;
//bool isBack = true;
//
//bool isDiving = false;
//int swimRotation = 0;
//int defaultRotRateX = 4096;
//
//
//bool bIsInAir = false;
//float BhopVelX = 0;
//float BhopVelY = 0;
//float BhopMultipier = 0.7;
//
//int currentMs = 0;
//
//void OnStart()
//{
//}
//
//void OnPlayerInWaterEnter()
//{
//	isDiving = true;
//	swimRotation = 0;
//	Game.Variables.SetRotationRateX(0);
//	Game.Variables.SetPrePivotZ(-20);
//
//	Game.Variables.SetWaterSpeed(700);
//	Game.Variables.SetWaterSpeed2(700);
//}
//
//void OnPlayerInWaterTick()
//{
//	if (swimRotation > -15000) {
//		swimRotation -= 70;
//		Game.Variables.SetRotationX(swimRotation);
//	}
//}
//
//void OnPlayerInWaterExit()
//{
//	isDiving = false;
//	swimRotation = 0;
//	Game.Variables.SetPrePivotZ(0);
//	Game.Variables.SetRotationRateX(20000);
//}
//
//void OnPlayerHealthUpdate(float oldHealth, float newHealth)
//{
//	/*Game.LogToConsole(
//		"Old Health: " + std::to_string(oldHealth) +
//		" | New Health: " + std::to_string(newHealth) +
//		" | Change: " + std::to_string(abs(newHealth - oldHealth))
//	);*/
//}
//
//void OnPlayerInAirEnter()
//{
//	/*isBackflipping = true;
//	isBack = (rand() % 100 + 1) >= 50;
//	flipRotation = isBack ? 0 : 65000;*/
//
//	Game.LogToConsole("Air");
//	bIsInAir = true;
//}
//
//void OnPlayerInAirTick()
//{
//	BhopVelX = Game.Variables.GetVelocityX();
//	BhopVelY = Game.Variables.GetVelocityY();
//
//	Game.LogToConsole("Hello");
//
//	//if (isBackflipping) {
//	//	if (isBack) {
//	//		flipRotation += 50;
//	//		if (flipRotation >= 65000) {
//	//			// Finished backclip
//	//			flipRotation = 0;
//	//			isBackflipping = false;
//	//		}
//	//	}
//	//	else {
//	//		flipRotation -= 50;
//	//		if (flipRotation <= 500) {
//	//			// Finished frontclip
//	//			flipRotation = 0;
//	//			isBackflipping = false;
//	//		}
//	//	}
//	//	Game.Variables.SetRotationX(flipRotation);
//	//}
//}
//
//void OnPlayerLand()
//{
//	Game.LogToConsole("Land");
//	bIsInAir = false;
//
//	Game.Delay(500).then([]
//	{
//		if (bIsInAir == true)
//		{
//			Game.Variables.SetVelocityX(BhopVelX);
//			Game.Variables.SetVelocityY(BhopVelY);
//			Game.LogToConsole("Player bhopped!");
//		}
//		else
//		{
//			Game.LogToConsole("Player failed to bhop!");
//		}
//	});
//}
//
//void OnPlayerHitJumpMagnetHit()
//{
//	Game.LogToConsole("Hit Jump Magnet (Auto Jump)");
//}
//
//void OnPlayerHitJumpMagnetDone()
//{
//	Game.LogToConsole("Landed Jump Magnet (Auto Jump)");
//}
//
//void OnPlayerHitBouncePadHit()
//{
//	Game.LogToConsole("Hit Bounce Pad");
//}
//
//void OnPlayerHitBouncePadDone()
//{
//	Game.LogToConsole("Landed Bounce Pad");
//}
//
//void OnPlayerDie()
//{
//	Game.LogToConsole("Player Died");
//}
//
//void OnPlayerRespawn()
//{
//	Game.LogToConsole("Player Respawned");
//}
//
//void OnPlayerMove(float x, float y, float z)
//{
//	Game.LogToConsole("Player Move | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Z: " + std::to_string(z));
//}
//
//void OnPlayerRotate(float x, float y, float z)
//{
//	Game.LogToConsole("Player Rotate | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + ", Z: " + std::to_string(z));
//}
//
//int currentMs = 0;
//void OnTick()
//{
//	if (bIsInAir == true)
//	{
//		currentMs += 1;
//		if (currentMs >= 50) {
//			currentMs = 0;
//			Game.LogToConsole("X: " + std::to_string(BhopVelX));
//			Game.LogToConsole("Y: " + std::to_string(BhopVelY));
//		}
//	}
//}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	//Game.Events.OnPlayerInWaterEnter = OnPlayerInWaterEnter;
	//Game.Events.OnPlayerInWaterTick = OnPlayerInWaterTick;
	//Game.Events.OnPlayerInWaterExit = OnPlayerInWaterExit;
	//Game.Events.OnPlayerHealthUpdate = OnPlayerHealthUpdate;
	Game.Events.OnPlayerInAirEnter = OnPlayerInAirEnter;
	//Game.Events.OnPlayerInAirTick = OnPlayerInAirTick;
	Game.Events.OnPlayerLand = OnPlayerLand;
    Game.Events.OnPlayerHitBouncePadHit = OnPlayerHitBouncePadHit;
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
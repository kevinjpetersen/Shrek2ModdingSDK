/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

bool isCarrying = false;

Shrek2Vector3 CarriedPosition = Shrek2Vector3(0, 0, 0);
Shrek2Actor* CarriedActor;

float CalculateDistance(Shrek2Vector3 p1, Shrek2Vector3 p2)
{
	float diffX = p1.X - p2.X;
	float diffY = p1.Y - p2.Y;
	float diffZ = p1.Z - p2.Z;
	return sqrt((diffY * diffY) + (diffX * diffX) + (diffZ * diffZ));
}

void OnActorList()
{
	if (isCarrying)
	{
		auto shrek = Game.Actors.GetCharacter(Shrek2CharacterTypes::Shrek);
		if (shrek)
		{
			if (CarriedActor)
			{
				CarriedPosition = Shrek2Vector3(shrek->Position.X, shrek->Position.Y, shrek->Position.Z + 100);
				CarriedActor->Position = CarriedPosition;
			}
		}
	}
}

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::E))
	{
		auto shrek = Game.Actors.GetCharacter(Shrek2CharacterTypes::Shrek);
		if (shrek)
		{
			auto actors = Game.Actors.GetActors({ 
				Shrek2ActorTypes::Coin, 
				Shrek2ActorTypes::CoinStack, 
				Shrek2ActorTypes::Donkey, 
				Shrek2ActorTypes::PunchingBag, 
				Shrek2ActorTypes::Shamrock, 
				Shrek2ActorTypes::BriarPatch, 
				Shrek2ActorTypes::BreakableCrate 
			});

			if (!actors.empty())
			{
				float currentDistance = 9999;
				for (int i = 0; i < actors.size(); i++)
				{
					auto actor = actors[i];

					float distance = CalculateDistance(shrek->Position, actor->Position);
					if (distance > 150) continue;

					if (distance <= currentDistance)
					{
						currentDistance = distance;
						CarriedActor = actor;
					}
				}

				if (CarriedActor)
				{
					isCarrying = true;
					shrek->CarriedActor = CarriedActor;
				}
			}
		}
	}

	if (Game.Input.OnKeyPress(Shrek2Input::LEFT_MOUSE_BUTTON))
	{
		isCarrying = false;
		CarriedActor = NULL;
	}
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
	Game.Events.OnActorList = OnActorList;

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
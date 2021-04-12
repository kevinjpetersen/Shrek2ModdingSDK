/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		auto donkey = Game.Actors.GetCharacter(Shrek2CharacterTypes::Donkey);
		if (donkey)
		{
			donkey->Rotation.X = 7000;
			donkey->Rotation.Y = 4000;
			donkey->Rotation.Z = 1300;
		}

		auto coinCollection = Game.Inventory.GetCoins();
		Game.LogToConsole("Name: " + donkey->GetName());
		Game.LogToConsole("Coins: " + std::to_string(Game.Inventory.GetCoins()));
	}

	if (Game.Input.OnKeyPress(Shrek2Input::H)) {
		auto donkey = Game.Actors.GetCharacter(Shrek2CharacterTypes::Donkey);
		if (donkey)
		{
			donkey->Rotation.X = 0;
			donkey->Rotation.Y = 0;
			donkey->Rotation.Z = 0;
		}
	}
}

void RenderUI()
{
	Shrek2UI::RenderText(Shrek2Rect(25, 300, 300, 100), "OnActorList TPS: " + std::to_string(Game.OnActorListTPS), Shrek2UI::GetColor(255, 255, 255), true);
}

void OnActorList()
{
	/*auto coin = Game.Actors.GetActor(Shrek2ActorTypes::Coin);
	if (coin)
	{
		auto pos = Shrek2Vector3(Game.Variables.GetPosition());
		pos.Z += 130;
		coin->Position = pos;
	}*/
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
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
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		system("cls");

		auto shreks = Game.Actors.GetActors(79);
		auto looktargets = Game.Actors.GetActors(2582);

		Game.LogToConsole("Shreks");
		Game.LogToConsole("------");

		if (shreks.empty() == false)
		{
			for (auto& p : shreks)
			{
				Game.LogToConsole(p->GetLabel());
			}
		}
		Game.LogToConsole("");

		Game.LogToConsole("KWLookTargets");
		Game.LogToConsole("------");
		for (auto& p : looktargets)
		{
			std::string label = p->GetLabel();
			if (label.empty()) continue;
			Game.LogToConsole(label);
		}
		Game.LogToConsole("");

		/*auto actor1 = Game.Actors.GetActor(79, "CoopPlayer1");
		auto actor2 = Game.Actors.GetActor(79, "CoopPlayer2");
		auto actor3 = Game.Actors.GetActor(79, "CoopPlayer3");
		auto actor4 = Game.Actors.GetActor(79, "CoopPlayer4");
		auto actor5 = Game.Actors.GetActor(79, "CoopPlayer5");
		auto actor6 = Game.Actors.GetActor(79, "CoopPlayer6");
		auto actor7 = Game.Actors.GetActor(79, "CoopPlayer7");
		auto actor8 = Game.Actors.GetActor(79, "CoopPlayer8");
		auto spawn = Game.Actors.GetActor(2582, "Coop_Player_Spawn");
		auto despawn1 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint1");
		auto despawn2 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint2");
		auto despawn3 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint3");
		auto despawn4 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint4");
		auto despawn5 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint5");
		auto despawn6 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint6");
		auto despawn7 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint7");
		auto despawn8 = Game.Actors.GetActor(2582, "Coop_Player_DespawnPoint8");


		if (actor1) std::cout << actor1->GetLabel() << std::endl;
		if (actor2) std::cout << actor2->GetLabel() << std::endl;
		if (actor3) std::cout << actor3->GetLabel() << std::endl;
		if (actor4) std::cout << actor4->GetLabel() << std::endl;
		if (actor5) std::cout << actor5->GetLabel() << std::endl;
		if (actor6) std::cout << actor6->GetLabel() << std::endl;
		if (actor7) std::cout << actor7->GetLabel() << std::endl;
		if (actor8) std::cout << actor8->GetLabel() << std::endl;
		if (spawn) std::cout << spawn->GetLabel() << std::endl;
		if (despawn1) std::cout << despawn1->GetLabel() << std::endl;
		if (despawn2) std::cout << despawn2->GetLabel() << std::endl;
		if (despawn3) std::cout << despawn3->GetLabel() << std::endl;
		if (despawn4) std::cout << despawn4->GetLabel() << std::endl;
		if (despawn5) std::cout << despawn5->GetLabel() << std::endl;
		if (despawn6) std::cout << despawn6->GetLabel() << std::endl;
		if (despawn7) std::cout << despawn7->GetLabel() << std::endl;
		if (despawn8) std::cout << despawn8->GetLabel() << std::endl;*/
		
		/*auto actor = Game.Actors.GetCharacter(Shrek2CharacterTypes::Shrek);
		std::cout << actor << std::endl;
		system("cls");
		auto actors = Game.Actors.GetActors(2582);

		for (auto& p : actors)
		{
			std::cout << p << std::endl;
			Game.LogToConsole(p->GetLabel());
			Game.LogToConsole("------");
		}*/
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

	Game.Initialize("Shrek 2 Twitch Emotes", true);

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
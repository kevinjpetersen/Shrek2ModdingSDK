/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

POINT MousePosition;

bool playHover = false;
bool settingsHover = false;
bool quitHover = false;

bool showMenu = true;

void OnTick()
{
	MousePosition = Game.GetMousePosition();

	playHover = Shrek2Utils::Overlap(Shrek2Vector2(MousePosition.x, MousePosition.y), Shrek2Vector2(Game.GetGameClientWidth() / 2 - 64, 280), Shrek2Vector2(128, 64));
	settingsHover = Shrek2Utils::Overlap(Shrek2Vector2(MousePosition.x, MousePosition.y), Shrek2Vector2(Game.GetGameClientWidth() / 2 - 64, 360), Shrek2Vector2(128, 64));
	quitHover = Shrek2Utils::Overlap(Shrek2Vector2(MousePosition.x, MousePosition.y), Shrek2Vector2(Game.GetGameClientWidth() / 2 - 64, 440), Shrek2Vector2(128, 64));

	if (Game.Input.OnKeyPress(Shrek2Input::Keys::LEFT_MOUSE_BUTTON))
	{
		if (showMenu)
		{
			if (playHover)
			{
				showMenu = false;
				Game.Input.SimulateKeyPress(Shrek2Input::Keys::ESCAPE);
				Game.Functions.OpenMap(Shrek2Maps::Shreks_Swamp);
				Game.LogToConsole("Play Button Clicked!");
			}
			else if (settingsHover)
			{
				Game.LogToConsole("Settings Button Clicked!");
			}
			else if (quitHover)
			{
				Game.LogToConsole("Quit Button Clicked!");
				exit(0);
			}
		}
	}
}

void RenderUI()
{
	if (showMenu)
	{
		if (Shrek2Utils::DoesEqual(Game.Variables.GetCurrentMap(), "Coop_MainMenu.unr"))
		{
			Shrek2UI::RenderTexture(Shrek2Textures::GetTexture("Logo"), Shrek2Position(Game.GetGameClientWidth() / 2 - 200, 50), 0);

			Shrek2UI::RenderTexture(Shrek2Textures::GetTexture(playHover ? "Button_Play_Hover" : "Button_Play"), Shrek2Position(Game.GetGameClientWidth() / 2 - 64, 280), 0);
			Shrek2UI::RenderTexture(Shrek2Textures::GetTexture(settingsHover ? "Button_Settings_Hover" : "Button_Settings"), Shrek2Position(Game.GetGameClientWidth() / 2 - 64, 360), 0);
			Shrek2UI::RenderTexture(Shrek2Textures::GetTexture(quitHover ? "Button_Quit_Hover" : "Button_Quit"), Shrek2Position(Game.GetGameClientWidth() / 2 - 64, 440), 0);
		}
	}
}

void OnMapLoad(Shrek2Maps oldMap, Shrek2Maps newMap, std::string rawMap) {
	if (Shrek2Utils::DoesEqual(Game.Variables.GetCurrentMap(), "Coop_MainMenu.unr"))
	{
		showMenu = true;
	}
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
	Shrek2Textures::AddTexture("logo.png", "Logo");

	Shrek2Textures::AddTexture("button_play.png", "Button_Play");
	Shrek2Textures::AddTexture("button_play_hover.png", "Button_Play_Hover");

	Shrek2Textures::AddTexture("button_settings.png", "Button_Settings");
	Shrek2Textures::AddTexture("button_settings_hover.png", "Button_Settings_Hover");

	Shrek2Textures::AddTexture("button_quit.png", "Button_Quit");
	Shrek2Textures::AddTexture("button_quit_hover.png", "Button_Quit_Hover");

	Shrek2UI::GameWindowSize = Game.GameWindowSize;
	Shrek2UI::RenderUI = RenderUI;
	Shrek2UI::Initialize();
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	Game.Events.OnActorList = OnActorList;
	Game.Events.OnMapLoad = OnMapLoad;

	Game.Initialize("Shrek 2 Test Mod", false);

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
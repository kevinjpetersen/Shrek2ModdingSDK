#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"
#include <algorithm> 

Shrek2 Game = Shrek2();

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		float x = Game.Variables.GetPositionX();
		float y = Game.Variables.GetPositionY();
		float z = Game.Variables.GetPositionZ();

		Game.LogToConsole(std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
	}
}

void RenderUI()
{
	/*std::string t = trigger1.Triggered ? "Yes" : "No";

	Shrek2UI::RenderText(
		Shrek2Rect(10, Game.GetGameWindowHeight() / 2 - 90, 400, 100),
		("Inside Trigger 1: " + t).c_str(),
		Shrek2UI::GetColor(0, 0, 255),
		true
	);*/

	//Shrek2UI::RenderText(Shrek2Rect(0, 0, 400, 100), "Player Health: " + std::to_string((int)Shrek2Maps::Beanstalk_bonus), Shrek2UI::GetColor(255, 0, 0), true);
	
	//Shrek2UI::RenderRectangle(Shrek2Rect(10, Game.GetGameWindowHeight() / 2 - 64, 128, 128), Shrek2UI::GetColor(insideTrigger ? 0 : 255, insideTrigger ? 255 : 0, 0));
	//Shrek2UI::RenderRectangle(Shrek2Rect(PlayerLocation.x, PlayerLocation.y, 10, 10), Shrek2UI::GetColor(255, 0, 0));



	//Sleep(1000 / 5);
	/*Shrek2UI::RenderTexture(Shrek2Textures::GetTexture("PIB"), Shrek2Position(Game.GetGameWindowWidth() / 2, Game.GetGameWindowHeight() / 2));
	Shrek2UI::RenderTexture(Shrek2Textures::GetTexture("M64"), Shrek2Position(350, 200), 45);
	Shrek2UI::RenderRectangle(Shrek2Rect(0, 0, 64, 64), Shrek2UI::GetColor(255, 255, 0));
	Shrek2UI::RenderRectangle(Shrek2Rect(0, 64, 64, 64), Shrek2UI::GetColor(255, 0, 0));*/

}

void OnTriggerEnter(Shrek2Trigger trigger)
{
	Game.LogToConsole(trigger.Name + " ENTER");
}

void OnTriggerExit(Shrek2Trigger trigger)
{
	Game.LogToConsole(trigger.Name + " EXIT");
}

void OnStart()
{
	//Game.Sounds.AddSound("Sounds/fanfare.wav", "Fanfare");
	//Game.Sounds.AddSound("Sounds/allstars.wav", "Allstars");
	//Game.Sounds.Play("Allstars");
	//Shrek2Textures::AddTexture("Images/pib.png", "PIB");
	//Shrek2Textures::AddTexture("Images/master64.jpg", "M64");

	Shrek2UI::GameWindowSize = Game.GameWindowSize;
	Shrek2UI::RenderUI = RenderUI;
	Shrek2UI::Initialize();
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;
	Game.Triggers.OnTriggerEnter = OnTriggerEnter;
	Game.Triggers.OnTriggerExit = OnTriggerExit;

	Game.Triggers.EnableDebugging = true;
	Game.Triggers.AddTrigger(
		Shrek2Trigger("Lillypad5", Shrek2Vector3(-13401.538086, -789.874084, -207.824005), Shrek2Vector3(2000, 100, 100))
	);

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
			Shrek2UI::StopUI();
			Sleep(1000);
		}
		break;
	}
	return TRUE;
}
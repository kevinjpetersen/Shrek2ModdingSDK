#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
//#include "Shrek2DirectX.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

void OnMapLoad(Shrek2Maps oldMap, Shrek2Maps newMap, std::string rawMap) {
	Game.LogToConsole("Old map: " + Game.Functions.MapIdToString(static_cast<int>(oldMap)) +
		" | New Map: " + Game.Functions.MapIdToString(static_cast<int>(newMap)));

	if (newMap == Shrek2Maps::Shreks_Swamp) {
		Game.LogToConsole("We're in SWAAAMP!");
	}
	else if (newMap == Shrek2Maps::The_Hunt_Part1) {
		Game.LogToConsole("It's hunting time!");
	}
}

void OnCharacterChanged(std::string oldCharacter, std::string newCharacter)
{
	if (Shrek2Utils::DoesEqual(newCharacter, "fionaogre")) {
		Game.LogToConsole("It was fiona all along!");
	}

	Game.LogToConsole("CHARACER CHANGE");

	//Game.LogToConsole("Old character: " + oldCharacter + " | New character: " + newCharacter);

	//Game.Delay(1000).then([]() {
	//	Game.Functions.CC("adminsay Hello 1");
	//	Game.Wait(1000);
	//	Game.Functions.CC("adminsay Hello 2");
	//	Game.Wait(1000);
	//	Game.Functions.CC("adminsay Hello 3");
	//	Game.Wait(1000);
	//	Game.Functions.CC("adminsay Hello 4");
	//	Game.Wait(1000);
	//	Game.Functions.CC("adminsay Hello 5");
	//	Game.Wait(1000);
	//	Game.Functions.CC("adminsay DONE");
	//});
	//Game.LogToConsole("KEEP RUNNING");
}

void OnPlayerInWaterEnter()
{
	Game.Events.OnCharacterChanged = NULL;
}

void OnPlayerInWaterExit() 
{
	Game.Events.OnCharacterChanged = OnCharacterChanged;
}

void OnTick()
{
	//Game.LogToConsole("Tick tock");
}

void RenderUI()
{
	Shrek2UI::RenderRectangle(Shrek2Rect(0, 0, 64, 64), Shrek2UI::GetColor(255, 255, 0));
	Shrek2UI::RenderRectangle(Shrek2Rect(0, 64, 64, 64), Shrek2UI::GetColor(255, 0, 0));
	Shrek2UI::RenderText(Shrek2Rect(50, 50, 200, 100), "Master_64 is a Shrekster!", Shrek2UI::GetColor(255, 0, 0), true);
	Shrek2UI::RenderTexture(Shrek2UI::Textures.sh2o_logo, D3DXVECTOR2(200, 200));
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
	Game.Events.OnMapLoad = OnMapLoad;
	Game.Events.OnCharacterChanged = OnCharacterChanged;
	Game.Events.OnTick = OnTick;
	Game.Events.OnPlayerInWaterEnter = OnPlayerInWaterEnter;
	Game.Events.OnPlayerInWaterExit = OnPlayerInWaterExit;

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
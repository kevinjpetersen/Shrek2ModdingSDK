/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"
#include "Entity.h"

Shrek2 Game = Shrek2();

std::vector<Entity*> LoadEntities(uintptr_t ptr)
{
	int failCounter = 0;
	std::vector<Entity*> entities;
	for (int i = 0; i < 9999; ++i)
	{
		uintptr_t pointer = *(uintptr_t*)(ptr + (i * 4));
		if (pointer)
		{
			failCounter = 0;
			Entity* entity = (Entity*)pointer;
			entities.push_back(entity);
		}
		else {
			failCounter++;
		}
		if (failCounter > 5)
			return entities;
	}
	return entities;
}

void ExecuteEntity(Entity* ent)
{
	std::string name1 = "";
	std::string name2 = "";

	MEMORY_BASIC_INFORMATION mbi0;
	VirtualQuery(ent, &mbi0, sizeof(mbi0));

	if (mbi0.Protect & PAGE_READWRITE)
	{

		MEMORY_BASIC_INFORMATION mbi1;
		VirtualQuery(ent->Name1, &mbi1, sizeof(mbi1));

		if (mbi1.Protect == PAGE_READWRITE)
		{
			if (ent->Name1 != nullptr) {
				std::wstring str = reinterpret_cast<wchar_t*>(ent->Name1);

				if (!str.empty())
				{
					name1 = Shrek2Utils::WS2String(str);
				}
			}
		}

		MEMORY_BASIC_INFORMATION mbi2;
		VirtualQuery(ent->Name2, &mbi2, sizeof(mbi2));

		if (mbi2.Protect == PAGE_READWRITE)
		{
			if (ent->Name2 != nullptr) {
				std::wstring str = reinterpret_cast<wchar_t*>(ent->Name2);

				if (!str.empty())
				{
					name2 = Shrek2Utils::WS2String(str);
				}
			}
		}
	}

	if (!name1.empty() || !name2.empty()) {
		bool hasName = false;
		if (!name1.empty())
		{
			if (!Shrek2Utils::Contains(name1, "?"))
			{
				std::cout << "Name 1: " << name1 << std::endl;
				hasName = true;
			}
		}
		if (!name2.empty())
		{
			if (!Shrek2Utils::Contains(name2, "?"))
			{
				std::cout << "Name 2: " << name2 << std::endl;
				hasName = true;
			}
		}

		if (hasName)
		{
			std::cout << "X: " << ent->Position.x << ", Y: " << ent->Position.y << ", Z: " << ent->Position.z << std::endl;
			std::cout << "Addr: " << ent << std::endl;
			std::cout << "----" << std::endl;
		}
	}
}

void ExecuteEntitySafely(Entity* ent) {
	__try {
		ExecuteEntity(ent);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {}
}

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G))
	{
		Game.Storage.SetFloat("PlayerX", Game.Variables.GetPositionX());
		Game.Storage.SetFloat("PlayerY", Game.Variables.GetPositionY());
		Game.Storage.SetFloat("PlayerZ", Game.Variables.GetPositionZ());
	}

	if (Game.Input.OnKeyPress(Shrek2Input::H))
	{
		auto pos = Shrek2Vector3(Game.Storage.GetFloat("PlayerX"), Game.Storage.GetFloat("PlayerY"), Game.Storage.GetFloat("PlayerZ"));
		Game.Variables.SetPosition(pos);
	}

	if (Game.Input.OnKeyPress(Shrek2Input::O))
	{
		Game.LogToConsole("Test: " + std::to_string(Game.Storage.GetLong("Bla bla")));
	}

	/*if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		system("CLS");

		DWORD addr = Shrek2Memory::GetAddr("Engine.dll", 0x004E85F0, 0x18C, 0x334, 0x30, 0x88);
		if (addr)
		{
			auto entities = LoadEntities(addr);
			if (entities.size() > 0)
			{
				Game.LogToConsole("Amount of Entities in Level: " + std::to_string(entities.size()));

				for (Entity* ent : entities)
				{
					ExecuteEntitySafely(ent);
				}
			}
			else {
				Game.LogToConsole("No entities found in this level.");
			}
		}
		else {
			Game.LogToConsole("Pointer doesn't point to anything!");
		}
	}*/
}

void RenderUI()
{
	Shrek2UI::RenderText(
		Shrek2Rect(10, Game.GetGameClientHeight() / 2 - 90, 400, 100),
		"Test Text",
		Shrek2UI::GetColorAlpha(255, 255, 255, 255),
		true
	);
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
/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;
using namespace std;

map<string, string> AvailableMods;
map<string, HINSTANCE> LoadedMods;

bool modsLoaded = false;

void LogError(std::string title, std::string message)
{
	try {
		std::cout << "[ERROR] [" << title << "] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}

void LogError(std::string title, char* message)
{
	try {
		std::cout << "[ERROR] [" << title << "] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}

void LogToConsole(std::string logMessage)
{
	try {
		std::cout << logMessage << std::endl;
	} catch(std::exception& ex) {}
}

void HideConsole()
{
	try {
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::HideConsole", ex.what());
	}
}

void ShowConsole()
{
	try {
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::ShowConsole", ex.what());
	}
}

bool IsConsoleVisible()
{
	try {
		return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::IsConsoleVisible", ex.what());
		return false;
	}
}

void LoadMods() {
	try {
		LogToConsole("Loading Mods..");

		for (const auto& [key, value] : AvailableMods) {
			HINSTANCE hModule = LoadLibraryA(value.c_str());

			if (hModule != NULL)
			{
				LoadedMods.insert(pair<string, HINSTANCE>(key, hModule));
				LogToConsole("Loaded Mod: " + key);
			}
			else
			{
				DWORD lastError = GetLastError();
				std::cout << "General failure. GetLastError returned " << std::hex << lastError << ".";
				LogToConsole("Failed to load mod: " + key);
			}
		}

		LogToConsole("Finished loading mods.");
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::LoadMods", ex.what());
	}
}

void UnloadMods() {
	try {
		LogToConsole("Unloading Mods..");

		for (const auto& [key, value] : LoadedMods) {
			if (value != NULL)
			{
				FreeLibrary(value);
			}
		}

		Sleep(100);
		LoadedMods.clear();
		LogToConsole("Finished unloading mods.");
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::UnloadMods", ex.what());
	}
}

DWORD GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD mod = (DWORD)(GetModuleHandle(shModule));
		DWORD base = *(DWORD*)(mod + baseAddress);

		if (base == 0) return NULL;

		DWORD pointerValue = *(DWORD*)(base + offset1);
		if (pointerValue == 0) return NULL;

		pointerValue = *(DWORD*)(pointerValue + offset2);
		if (pointerValue == 0) return NULL;

		pointerValue = *(DWORD*)(pointerValue + offset3);
		if (pointerValue == 0) return NULL;

		pointerValue = (pointerValue + offset4);
		if (pointerValue == 0) return NULL;

		return pointerValue;
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::GetAddr", ex.what());
		return NULL;
	}
}

float ReadFloat(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			float fValue = *(float*)(addr);
			return fValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::ReadFloat", ex.what());
		return 0;
	}
}

float GetPlayerHealth() {
	try {
		return ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4E0);
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::GetPlayerHealth", ex.what());
		return 0;
	}
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	try {
		FILE* fp = NULL;

		AllocConsole();
		freopen_s(&fp, "CONOUT$", "w", stdout);
		HideConsole();

		LogToConsole("Waiting for Shrek 2 to open..");
		bool findWindow = true;
		while (findWindow) {
			try {
				float health = GetPlayerHealth();
				if (health > 0) {
					findWindow = false;
					break;
				}
				Sleep(500);
			}
			catch (std::exception& ex)
			{
				LogError("ModLoader::InitializationThread::FindWindow", ex.what());
				Sleep(500);
			}
		}

		// Find Mods
		std::string path = "Shrek 2 Mods/";
		LogToConsole("Finding Mods..");

		for (const auto& p : fs::directory_iterator(path)) {
			if (p.is_directory()) {
				for (const auto& entry : fs::directory_iterator(p.path())) {
					string modName = fs::path(entry.path()).stem().u8string();

					if (fs::path(entry.path()).extension() == ".dll") {
						AvailableMods.insert(pair<string, string>(modName, entry.path().u8string()));
						LogToConsole("Available Mod: " + modName);
					}
				}
			}
		}

		LogToConsole("Finished finding mods.");

		if (AvailableMods.size() > 0) {
			LoadMods();
			modsLoaded = true;
		}
		else {
			LogToConsole("No Mods found. Press Numpad 0 to try again!");
		}

		while (true) {
			try {
				Sleep(1);

				if (IsConsoleVisible())
				{
					// Disable Modloader and Mods
					if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
						if (LoadedMods.size() > 0) {
							UnloadMods();
						}
						else
						{
							LogToConsole("No mods found to unload.");
						}
						break;
					}

					// Toggle Mods
					if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
						if (modsLoaded == false) {
							modsLoaded = true;
							if (AvailableMods.size() > 0) {
								if (LoadedMods.size() <= 0) {
									LoadMods();
								}
								else
								{
									LogToConsole("You cannot load mods when they're already loaded.");
								}
							}
							else
							{
								LogToConsole("No mods found to load.");
							}
						}
						else {
							modsLoaded = false;
							if (LoadedMods.size() > 0) {
								UnloadMods();
							}
							else
							{
								LogToConsole("No mods found to unload.");
							}
						}
					}

					// Toggle Debug Console
					if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
						if (IsConsoleVisible()) {
							HideConsole();
						}
						else {
							ShowConsole();
						}
					}
				}
			}
			catch (std::exception& ex)
			{
				LogError("ModLoader::InitializationThread::MainLoop", ex.what());
				Sleep(100);
			}
		}

		if (fp != NULL) {
			fclose(fp);
		}
		FreeConsole();

		Sleep(100);
		FreeLibraryAndExitThread(hModule, 0);
		return 0;
	}
	catch (std::exception& ex)
	{
		LogError("ModLoader::InitializationThread::Outer", ex.what());
		try {
			system("pause");
		} catch(std::exception& ex2){}
		return 0;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializationThread, NULL, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

__declspec(dllexport) int APIENTRY Func(LPVOID lpParam)
{
	return 0;
}


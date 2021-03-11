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

void LogToConsole(std::string logMessage)
{
	std::cout << logMessage << std::endl;
}

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

bool BackupDefUser() {
	std::ifstream  src("DefUser.ini", std::ios::binary);
	std::ofstream  dst("Backup_DefUser.ini", std::ios::binary);
	dst << src.rdbuf();

	return true;
}

inline bool FileExists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

bool SetupCCSKeybindings(string mods) {
	if (FileExists("Backup_DefUser.ini") == false) {
		LogToConsole("First time setting up keybinds. Backing up DefUser.ini..");
		bool backedUp = BackupDefUser();
		if (backedUp) {
			LogToConsole("Successfully backed up DefUser.ini to Backup_DefUser.ini");
		}
	}

	std::ifstream  src("DefUser.ini", std::ios::binary);
	std::ofstream  dst("Temp_DefUser.ini", std::ios::binary);
	dst << src.rdbuf();

	ifstream in("Temp_DefUser.ini");
	ofstream out("DefUser.ini");
	string wordToCheck("F24=");
	string wordToReplaceWith("F24=" + mods);

	if (!in)
	{
		return false;
	}

	if (!out)
	{
		return false;
	}

	bool firstTime = false;

	string line;
	while (getline(in, line))
	{
		size_t pos = line.find(wordToCheck);
		if (pos != string::npos) {
			LogToConsole("Setting keybindings..");
			line = wordToReplaceWith;
			LogToConsole("Finished setting up keybindings.");
		}

		out << line << '\n';
	}

	in.close();
	out.close();

	return true;
}

void LoadMods() {
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
			LogToConsole("Failed to load mod: " + key);
		}
	}

	LogToConsole("Finished loading mods.");
}

void UnloadMods() {
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

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	FILE* fp = NULL;

	AllocConsole();
	freopen_s(&fp, "CONOUT$", "w", stdout);
	//HideConsole();

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

	int i = 1;
	string modsKeybinding = "";

	for (const auto& [key, value] : AvailableMods)
	{
		string modName = key;
		remove(modName.begin(), modName.end(), ' ');
		if (i == AvailableMods.size()) {
			modsKeybinding += "exec " + modName;
		}
		else {
			modsKeybinding += "exec " + modName + " | ";
		}

		i++;
	}

	SetupCCSKeybindings(modsKeybinding);

	if (AvailableMods.size() > 0) {
		LoadMods();
	}
	else {
		LogToConsole("No Mods found. Press Numpad 2 to try again!");
	}

	while (true) {
		Sleep(1);

		// Disable Mods
		if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
			break;
		}

		// Eject Mods
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			if (LoadedMods.size() > 0) {
				UnloadMods();
			}
			else
			{
				LogToConsole("No mods found to unload.");
			}
		}

		// Load Mods
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
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

		// Toggle Debug Console
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			if (IsConsoleVisible()) {
				HideConsole();
			}
			else {
				ShowConsole();
			}
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


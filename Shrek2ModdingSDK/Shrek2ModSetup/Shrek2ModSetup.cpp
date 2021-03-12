// Shrek2ModExecutor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include <string>
#include <ShlObj.h>
using namespace std;
namespace fs = std::filesystem;
map<string, string> AvailableMods;

void LogToConsole(std::string logMessage)
{
	std::cout << logMessage << std::endl;
}

bool BackupDefUser() {
	fs::copy_file("DefUser.ini", "Backup_DefUser.ini");
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

	fs::copy_file("DefUser.ini", "Temp_DefUser.ini");

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

	fs::remove("Temp_DefUser.ini");
	return true;
}

int main()
{
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
	LogToConsole(modsKeybinding);
	system("pause");
	return 0;
}

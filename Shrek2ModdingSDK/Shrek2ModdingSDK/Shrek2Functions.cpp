/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

void Shrek2Functions::ExecuteConsoleCommand(std::string command)
{
	ExecCC(command);
}

void Shrek2Functions::ExecuteConsoleCommands(std::list<std::string> commands)
{
	ExecCCS(commands);
}

void Shrek2Functions::CC(std::string command)
{
	ExecCC(command);
}

void Shrek2Functions::CCS(std::list<std::string> commands)
{
	ExecCCS(commands);
}

void Shrek2Functions::OpenMap(Shrek2Maps map)
{
	try {
		int mapId = static_cast<int>(map);
		std::string mapName = MapIdToString(mapId);
		CC("open " + mapName);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Functions::OpenMap", ex.what());
	}
}

void Shrek2Functions::OpenMap(std::string mapName)
{
	CC("open " + mapName);
}

void Shrek2Functions::Ghost()
{
	CC("ghost");
}

void Shrek2Functions::Walk()
{
	CC("walk");
}

void Shrek2Functions::Fly()
{
	CC("fly");
}

void Shrek2Functions::ToggleFreeCam()
{
	CCS({
		"set shgame.version bdebugenabled true",
		"set kwgame.kwversion bdebugenabled true",
		"freecam"
		});
}

void Shrek2Functions::DeleteSaveGame(int slot)
{
	try {
		_DeleteSaveGame(slot);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Functions::DeleteSaveGame", ex.what());
	}
}

void Shrek2Functions::ExecCC(std::string command)
{
	try {
		std::ofstream execFile(DllName);
		execFile << command << std::endl;
		execFile.close();
		Exec();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Functions::ExecCC", ex.what());
	}
}

void Shrek2Functions::ExecCCS(std::list<std::string> commands)
{
	try {
		std::ofstream execFile(DllName);
		for (auto const& cmd : commands) {
			execFile << cmd << std::endl;
		}
		execFile.close();
		Exec();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Functions::ExecCCS", ex.what());
	}
}

void Shrek2Functions::Exec()
{
	try {
		PostMessage(WindowHandle, WM_KEYDOWN, (int)0x87, 0);
		PostMessage(WindowHandle, WM_KEYUP, (int)0x87, 0);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Functions::Exec", ex.what());
	}
}

std::string Shrek2Functions::MapIdToString(int mapId)
{
	switch (mapId) {
	case 1: return "1_Shreks_Swamp";
	case 2: return "2_Carriage_Hijack";
	case 3: return "3_The_Hunt_Part1";
	case 4: return "3_The_Hunt_Part2";
	case 5: return "3_The_Hunt_Part3";
	case 6: return "3_The_Hunt_Part4";
	case 7: return "4_FGM_Office";
	case 8: return "4_FGM_PIB";
	case 9: return "5_FGM_Donkey";
	case 10: return "6_Hamlet";
	case 11: return "6_Hamlet_End";
	case 12: return "6_Hamlet_Mine";
	case 13: return "7_Prison_Donkey";
	case 14: return "8_Prison_PIB";
	case 15: return "9_Prison_Shrek";
	case 16: return "10_Castle_Siege";
	case 17: return "11_FGM_Battle";
	case 18: return "Beanstalk_bonus";
	case 19: return "Beanstalk_bonus_dawn";
	case 20: return "Beanstalk_bonus_knight";
	case 21: return "Book_FrontEnd";
	case 22: return "Book_Story_1";
	case 23: return "Book_Story_2";
	case 24: return "Book_Story_3";
	case 25: return "Book_Story_4";
	case 26: return "Book_StoryBook";
	case 27: return "Credits";
	case 28: return "Entry";
	case 29: return "SH2_Preamble";
	default: return "Book_FrontEnd";
	}
}

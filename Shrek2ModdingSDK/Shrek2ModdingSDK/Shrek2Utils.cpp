/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

std::string Shrek2Utils::FloatToLPCSTR(float fValue) {
	try {
		char buff[100];
		sprintf(buff, "%.3f", fValue);
		std::string p = buff;
		return p;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::FloatToLPCSTR", ex.what());
		return "";
	}
}

std::string Shrek2Utils::FloatToLPCSTRRaw(float fValue) {
	try {
		char buff[100];
		sprintf(buff, "%f", fValue);
		std::string p = buff;
		return p;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::FloatToLPCSTRRaw", ex.what());
		return "";
	}
}

std::string Shrek2Utils::IntToLPCSTRRaw(int fValue) {
	try {
		char buff[100];
		sprintf(buff, "%i", fValue);
		std::string p = buff;
		return p;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::IntToLPCSTRRaw", ex.what());
		return "";
	}
}

std::string Shrek2Utils::WS2String(const std::wstring& wstr)
{
	try {
		int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0);
		return strTo;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::WS2String", ex.what());
		return "";
	}
}

Shrek2Maps Shrek2Utils::MapStringToMap(std::string map)
{
	try {
		map = StringToLower(map);
		std::string formattedMap = ReplaceFirstOccurrence(map, ".unr", "");
		formattedMap = ReplaceFirstOccurrence(formattedMap, ".UNR", "");

		if (strcmp(formattedMap.c_str(), "1_shreks_swamp") == 0) return Shrek2Maps::Shreks_Swamp;
		if (strcmp(formattedMap.c_str(), "2_carriage_hijack") == 0) return Shrek2Maps::Carriage_Hijack;
		if (strcmp(formattedMap.c_str(), "3_the_hunt_part1") == 0) return Shrek2Maps::The_Hunt_Part1;
		if (strcmp(formattedMap.c_str(), "3_the_hunt_part2") == 0) return Shrek2Maps::The_Hunt_Part2;
		if (strcmp(formattedMap.c_str(), "3_the_hunt_part3") == 0) return Shrek2Maps::The_Hunt_Part3;
		if (strcmp(formattedMap.c_str(), "3_the_hunt_part4") == 0) return Shrek2Maps::The_Hunt_Part4;
		if (strcmp(formattedMap.c_str(), "4_fgm_office") == 0) return Shrek2Maps::FGM_Office;
		if (strcmp(formattedMap.c_str(), "4_fgm_pib") == 0) return Shrek2Maps::FGM_PIB;
		if (strcmp(formattedMap.c_str(), "5_fgm_donkey") == 0) return Shrek2Maps::FGM_Donkey;
		if (strcmp(formattedMap.c_str(), "6_hamlet") == 0) return Shrek2Maps::Hamlet;
		if (strcmp(formattedMap.c_str(), "6_hamlet_end") == 0) return Shrek2Maps::Hamlet_End;
		if (strcmp(formattedMap.c_str(), "6_hamlet_mine") == 0) return Shrek2Maps::Hamlet_Mine;
		if (strcmp(formattedMap.c_str(), "7_prison_donkey") == 0) return Shrek2Maps::Prison_Donkey;
		if (strcmp(formattedMap.c_str(), "8_prison_pib") == 0) return Shrek2Maps::Prison_PIB;
		if (strcmp(formattedMap.c_str(), "9_prison_shrek") == 0) return Shrek2Maps::Prison_Shrek;
		if (strcmp(formattedMap.c_str(), "10_castle_siege") == 0) return Shrek2Maps::Castle_Siege;
		if (strcmp(formattedMap.c_str(), "11_fgm_battle") == 0) return Shrek2Maps::FGM_Battle;
		if (strcmp(formattedMap.c_str(), "beanstalk_bonus") == 0) return Shrek2Maps::Beanstalk_bonus;
		if (strcmp(formattedMap.c_str(), "beanstalk_bonus_dawn") == 0) return Shrek2Maps::Beanstalk_bonus_dawn;
		if (strcmp(formattedMap.c_str(), "beanstalk_bonus_knight") == 0) return Shrek2Maps::Beanstalk_bonus_knight;
		if (strcmp(formattedMap.c_str(), "book_frontend") == 0) return Shrek2Maps::Book_FrontEnd;
		if (strcmp(formattedMap.c_str(), "book_story_1") == 0) return Shrek2Maps::Book_Story_1;
		if (strcmp(formattedMap.c_str(), "book_story_2") == 0) return Shrek2Maps::Book_Story_2;
		if (strcmp(formattedMap.c_str(), "book_story_3") == 0) return Shrek2Maps::Book_Story_3;
		if (strcmp(formattedMap.c_str(), "book_story_4") == 0) return Shrek2Maps::Book_Story_4;
		if (strcmp(formattedMap.c_str(), "book_storybook") == 0) return Shrek2Maps::Book_StoryBook;
		if (strcmp(formattedMap.c_str(), "credits") == 0) return Shrek2Maps::Credits;
		if (strcmp(formattedMap.c_str(), "entry") == 0) return Shrek2Maps::Entry;

		return Shrek2Maps::Unknown;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::MapStringToMap", ex.what());
		return Shrek2Maps::Unknown;
	}
}

std::string Shrek2Utils::StringToLower(std::string str)
{
	try {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::StringToLower", ex.what());
		return "";
	}
}

std::string Shrek2Utils::ReplaceFirstOccurrence(std::string& s, const std::string& toReplace, const std::string& replaceWith)
{
	try {
		std::size_t pos = s.find(toReplace);
		if (pos == std::string::npos) return s;
		return s.replace(pos, toReplace.length(), replaceWith);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::ReplaceFirstOccurrence", ex.what());
		return "";
	}
}

bool Shrek2Utils::DoesEqual(std::string str1, std::string str2)
{
	try {
		return std::strcmp(str1.c_str(), str2.c_str()) == 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::DoesEqual", ex.what());
		return false;
	}
}

bool Shrek2Utils::DoesEqualForced(std::string str1, std::string str2)
{
	try {
		if (str1.size() != str2.size()) {
			return false;
		}
		for (std::string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
			if (tolower(static_cast<unsigned char>(*c1)) != tolower(static_cast<unsigned char>(*c2))) {
				return false;
			}
		}
		return true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::DoesEqualForced", ex.what());
		return false;
	}
}

RECT Shrek2Utils::GetWindowSize(HWND windowHandle)
{
	try {
		RECT windowRect;
		GetWindowRect(windowHandle, &windowRect);
		return windowRect;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::GetWindowSize", ex.what());
		return RECT();
	}
}

RECT Shrek2Utils::GetClientSize(HWND windowHandle)
{
	try {
		RECT clientRect;
		GetClientRect(windowHandle, &clientRect);
		return clientRect;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::GetClientSize", ex.what());
		return RECT();
	}
}

std::vector<std::string> Shrek2Utils::SplitString(const std::string& stringToSplit, const std::string& regexPattern)
{
	try {
		std::vector<std::string> result;

		const std::regex rgx(regexPattern);
		std::sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);

		for (std::sregex_token_iterator end; iter != end; ++iter)
		{
			result.push_back(iter->str());
		}

		return result;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::SplitString", ex.what());
		return {};
	}
}

bool Shrek2Utils::Contains(std::string source, std::string find)
{
	try {
		return source.find(find) != std::string::npos;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::Contains", ex.what());
		return false;
	}
}

bool Shrek2Utils::ContainsForced(std::string source, std::string find)
{
	try {
		std::transform(source.begin(), source.end(), source.begin(), ::tolower);
		std::transform(find.begin(), find.end(), find.begin(), ::tolower);

		return source.find(find) != std::string::npos;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::ContainsForced", ex.what());
		return false;
	}
}

bool Shrek2Utils::Overlap(Shrek2Vector2 point, Shrek2Vector2 position, Shrek2Vector2 size)
{
	try {
		if (point.X > position.X && point.X < position.X + size.X && point.Y > position.Y && point.Y < position.Y + size.Y)
			return true;

		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::Overlap", ex.what());
		return false;
	}
}

bool Shrek2Utils::Overlap(Shrek2Vector2 point, Shrek2Rect position, Shrek2Vector2 size)
{
	try {
		if (point.X > position.X && point.X < position.X + size.X && point.Y > position.Y && point.Y < position.Y + size.Y)
			return true;

		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::Overlap", ex.what());
		return false;
	}
}

bool Shrek2Utils::Overlap(Shrek2Vector2 point, Shrek2Position position, Shrek2Vector2 size)
{
	try {
		if (point.X > position.X && point.X < position.X + size.X && point.Y > position.Y && point.Y < position.Y + size.Y)
			return true;

		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Utils::Overlap", ex.what());
		return false;
	}
}

int Shrek2Utils::GameToCharacterType(int gameCharacterId)
{
	switch (gameCharacterId)
	{
	case 1: return static_cast<int>(Shrek2CharacterTypes::Shrek);
	case 2: return static_cast<int>(Shrek2CharacterTypes::Donkey);
	case 3: return static_cast<int>(Shrek2CharacterTypes::PIB);
	case 4: return static_cast<int>(Shrek2CharacterTypes::Steed);
	case 5: return static_cast<int>(Shrek2CharacterTypes::ShrekHuman);
	default: static_cast<int>(Shrek2CharacterTypes::Unknown);
	}
}

std::string Shrek2Utils::GameToCharacterName(int gameCharacterId)
{
	switch (gameCharacterId)
	{
	case 1: return "Shrek";
	case 2: return "Donkey";
	case 3: return "PIB";
	case 4: return "Steed";
	case 5: return "Shrek Human";
	default: "Unknown";
	}
}

bool Shrek2Utils::ContainsInVector(std::vector<std::string> list, std::string value)
{
	return (std::find(list.begin(), list.end(), value) != list.end());
}


void Shrek2Utils::RemoveNullTerminators(std::string& str)
{
	str.erase(std::find(str.begin(), str.end(), '\0'), str.end());
}


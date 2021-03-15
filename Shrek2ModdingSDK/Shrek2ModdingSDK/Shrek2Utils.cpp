#include "Shrek2ModdingSDK.h"

std::string Shrek2Utils::FloatToLPCSTR(float fValue) {
	char buff[100];
	sprintf(buff, "%.3f", fValue);
	std::string p = buff;
	return p;
}

std::string Shrek2Utils::FloatToLPCSTRRaw(float fValue) {
	char buff[100];
	sprintf(buff, "%f", fValue);
	std::string p = buff;
	return p;
}

std::string Shrek2Utils::IntToLPCSTRRaw(int fValue) {
	char buff[100];
	sprintf(buff, "%i", fValue);
	std::string p = buff;
	return p;
}

std::string Shrek2Utils::WS2String(const std::wstring& wstr)
{
	int size_needed = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), 0, 0, 0, 0);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), int(wstr.length() + 1), &strTo[0], size_needed, 0, 0);
	return strTo;
}

Shrek2Maps Shrek2Utils::MapStringToMap(std::string map)
{
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

std::string Shrek2Utils::StringToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string Shrek2Utils::ReplaceFirstOccurrence(std::string& s, const std::string& toReplace, const std::string& replaceWith)
{
	std::size_t pos = s.find(toReplace);
	if (pos == std::string::npos) return s;
	return s.replace(pos, toReplace.length(), replaceWith);
}

bool Shrek2Utils::DoesEqual(std::string str1, std::string str2)
{
	return std::strcmp(str1.c_str(), str2.c_str()) == 0;
}

RECT Shrek2Utils::GetWindowSize(HWND windowHandle)
{
	RECT windowRect;
	GetWindowRect(windowHandle, &windowRect);
	return windowRect;
}

std::vector<std::string> Shrek2Utils::SplitString(const std::string& stringToSplit, const std::string& regexPattern)
{
	std::vector<std::string> result;

	const std::regex rgx(regexPattern);
	std::sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);

	for (std::sregex_token_iterator end; iter != end; ++iter)
	{
		result.push_back(iter->str());
	}

	return result;
}

#pragma once
class Shrek2Utils
{
public:
	static std::string FloatToLPCSTR(float fValue);
	static std::string FloatToLPCSTRRaw(float fValue);
	static std::string IntToLPCSTRRaw(int fValue);
	static void SaveToDisk(std::string data, std::string fileName);
	static std::string WS2String(const std::wstring& wstr);
	static Shrek2Maps MapStringToMap(std::string map);
	static std::string StringToLower(std::string str);
	static std::string ReplaceFirstOccurrence(std::string& s, const std::string& toReplace, const std::string& replaceWith);
	static bool DoesEqual(std::string str1, std::string str2);
};


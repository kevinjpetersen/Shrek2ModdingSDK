#pragma once
class Shrek2Utils
{
public:
	static std::string FloatToLPCSTR(float fValue);
	static std::string FloatToLPCSTRRaw(float fValue);
	static std::string IntToLPCSTRRaw(int fValue);
	static void SaveToDisk(std::string data, std::string fileName);
	static std::string WS2String(const std::wstring& wstr);
};


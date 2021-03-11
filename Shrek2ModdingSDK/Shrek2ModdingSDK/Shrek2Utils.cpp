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

/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

bool Shrek2Memory::WriteFloat(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			*(float*)(addr) = fValue;
			return true;
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::WriteFloat", ex.what());
		return false;
	}
}

float Shrek2Memory::ReadFloat(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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
		Shrek2Logging::LogError("Shrek2Memory::ReadFloat", ex.what());
		return 0;
	}
}

bool Shrek2Memory::WriteInt(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			*(int*)(addr) = iValue;
			return true;
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::WriteInt", ex.what());
		return false;
	}
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			int iValue = *(int*)(addr);
			return iValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadInt1", ex.what());
		return 0;
	}
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1);
		if (addr) {
			int iValue = *(int*)(addr);
			return iValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadInt2", ex.what());
		return 0;
	}
}

bool Shrek2Memory::WriteShortInt(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			*(short int*)(addr) = iValue;
			return true;
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::WriteShortInt", ex.what());
		return false;
	}
}

short int Shrek2Memory::ReadShortInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			short int iValue = *(short int*)(addr);
			return iValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadShortInt", ex.what());
		return 0;
	}
}

bool Shrek2Memory::WriteByte(byte bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			*(byte*)(addr) = bValue;
			return true;
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::WriteByte", ex.what());
		return false;
	}
}

byte Shrek2Memory::ReadByte(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			byte fValue = *(byte*)(addr);
			return fValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadByte", ex.what());
		return 0;
	}
}

bool Shrek2Memory::WriteBool(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			*(byte*)(addr) = bValue;
			return true;
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::WriteBool", ex.what());
		return false;
	}
}

bool Shrek2Memory::ReadBool(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			byte fValue = *(byte*)(addr);
			return fValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadBool", ex.what());
		return 0;
	}
}

std::string Shrek2Memory::ReadText(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4)
{
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			DWORD addr2 = *(DWORD*)(addr);
			if (addr2) {
				std::wstring str = reinterpret_cast<wchar_t*>(addr2);
				return Shrek2Utils::WS2String(str);
			}
		}
		return "";
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadText", ex.what());
		return "";
	}
}

std::wstring Convert(const std::wstring& s)
{
	try {
		if (s.empty())
			return std::wstring();

		int len = WideCharToMultiByte(858, 0, s.c_str(), s.length(), NULL, 0, NULL, NULL);
		if (len == 0)
			throw std::runtime_error("WideCharToMultiByte() failed");

		std::vector<char> bytes(len);

		len = WideCharToMultiByte(858, 0, s.c_str(), s.length(), &bytes[0], len, NULL, NULL);
		if (len == 0)
			throw std::runtime_error("WideCharToMultiByte() failed");

		len = MultiByteToWideChar(CP_ACP, 0, &bytes[0], bytes.size(), NULL, 0);
		if (len == 0)
			throw std::runtime_error("MultiByteToWideChar() failed");

		std::wstring result;
		result.resize(len);

		len = MultiByteToWideChar(CP_ACP, 0, &bytes[0], bytes.size(), &result[0], len);
		if (len == 0)
			throw std::runtime_error("MultiByteToWideChar() failed");

		return result;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::Convert", ex.what());
		return NULL;
	}
}

char* Shrek2Memory::ReadChar(LPCSTR shModule, DWORD baseAddress, DWORD offset1)
{
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1);

		if (addr) {

			char* str = reinterpret_cast<char*>(addr);
			char dest[4096];
			std::memcpy(dest, str, sizeof dest);
			return dest;
		}
		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadChar", ex.what());
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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
		Shrek2Logging::LogError("Shrek2Memory::GetAddr1", ex.what());
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
	try {
		DWORD mod = (DWORD)(GetModuleHandle(0));
		DWORD base = *(DWORD*)(mod + baseAddress);

		if (base == 0) return NULL;

		DWORD pointerValue = (base + offset1);
		if (pointerValue == 0) return NULL;

		return pointerValue;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::GetAddr2", ex.what());
		return NULL;
	}
}
/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"
#include <excpt.h>

int filter(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	try {
		if (code == EXCEPTION_ACCESS_VIOLATION)
		{
			Shrek2Logging::LogError("Shrek2Memory", "Access Violation Exception");
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else
		{
			Shrek2Logging::LogError("Shrek2Memory", "SEH Exception");
			return EXCEPTION_CONTINUE_SEARCH;
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::Filter", ex.what());
	}
}

bool Shrek2Memory::WriteFloat(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return WriteFloatSafe(fValue, shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

float Shrek2Memory::ReadFloat(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return ReadFloatSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

bool Shrek2Memory::WriteInt(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return WriteIntSafe(iValue, shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return ReadIntSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3) {
	__try {
		return ReadIntSafe(shModule, baseAddress, offset1, offset2, offset3);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
	__try {
		return ReadIntSafe(shModule, baseAddress, offset1);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

bool Shrek2Memory::WriteShortInt(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return WriteShortIntSafe(iValue, shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

short int Shrek2Memory::ReadShortInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return ReadShortIntSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

bool Shrek2Memory::WriteByte(byte bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return WriteByteSafe(bValue, shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

byte Shrek2Memory::ReadByte(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return ReadByteSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return 0;
	}
}

bool Shrek2Memory::WriteBool(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return WriteBoolSafe(bValue, shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

bool Shrek2Memory::ReadBool(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return ReadBoolSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return false;
	}
}

wchar_t* Shrek2Memory::ReadText(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4)
{
	__try {
		return ReadTextSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

wchar_t* Shrek2Memory::ReadText(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3)
{
	__try {
		return ReadTextSafe(shModule, baseAddress, offset1, offset2, offset3);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

char* Shrek2Memory::ReadChar(LPCSTR shModule, DWORD baseAddress, DWORD offset1)
{
	__try {
		return ReadCharSafe(shModule, baseAddress, offset1);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	__try {
		return GetAddrSafe(shModule, baseAddress, offset1, offset2, offset3, offset4);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
	__try {
		return GetAddrSafe(shModule, baseAddress, offset1);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3) {
	__try {
		return GetAddrSafe(shModule, baseAddress, offset1, offset2, offset3);
	}
	__except (filter(GetExceptionCode(), GetExceptionInformation()))
	{
		return NULL;
	}
}

// Safe Memory Functions
bool Shrek2Memory::WriteFloatSafe(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

float Shrek2Memory::ReadFloatSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

bool Shrek2Memory::WriteIntSafe(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

int Shrek2Memory::ReadIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

int Shrek2Memory::ReadIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3) {
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3);
		if (addr) {
			int iValue = *(int*)(addr);
			return iValue;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadInt3", ex.what());
		return 0;
	}
}

int Shrek2Memory::ReadIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
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

bool Shrek2Memory::WriteShortIntSafe(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

short int Shrek2Memory::ReadShortIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

bool Shrek2Memory::WriteByteSafe(byte bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

byte Shrek2Memory::ReadByteSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

bool Shrek2Memory::WriteBoolSafe(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

bool Shrek2Memory::ReadBoolSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

wchar_t* Shrek2Memory::ReadTextSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4)
{
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
		if (addr) {
			DWORD addr2 = *(DWORD*)(addr);
			if (addr2) {
				wchar_t* str = reinterpret_cast<wchar_t*>(addr2);
				if (str) {
					return str;
				}
				return NULL;
			}
		}
		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadText", ex.what());
		return NULL;
	}
}

wchar_t* Shrek2Memory::ReadTextSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3)
{
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3);
		if (addr) {
			DWORD addr2 = *(DWORD*)(addr);
			if (addr2) {
				wchar_t* str = reinterpret_cast<wchar_t*>(addr2);
				if (str) {
					return str;
				}
				return NULL;
			}
		}
		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadText", ex.what());
		return NULL;
	}
}

char* Shrek2Memory::ReadCharSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1)
{
	try {
		DWORD addr = GetAddr(shModule, baseAddress, offset1);

		if (addr) {
			char* str = reinterpret_cast<char*>(addr);
			return str;
		}
		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::ReadChar", ex.what());
		return NULL;
	}
}

DWORD Shrek2Memory::GetAddrSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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

DWORD Shrek2Memory::GetAddrSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1) {
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

DWORD Shrek2Memory::GetAddrSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3) {
	try {
		DWORD mod = (DWORD)(GetModuleHandle(shModule));
		DWORD base = *(DWORD*)(mod + baseAddress);

		if (base == 0) return NULL;

		DWORD pointerValue = *(DWORD*)(base + offset1);
		if (pointerValue == 0) return NULL;

		pointerValue = *(DWORD*)(pointerValue + offset2);
		if (pointerValue == 0) return NULL;

		pointerValue = (pointerValue + offset3);
		if (pointerValue == 0) return NULL;

		return pointerValue;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Memory::GetAddr3", ex.what());
		return NULL;
	}
}
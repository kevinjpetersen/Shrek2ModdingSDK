#include "Shrek2ModdingSDK.h"

bool Shrek2Memory::WriteFloat(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		*(float*)(addr) = fValue;
		return true;
	}
	return false;
}

float Shrek2Memory::ReadFloat(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		float fValue = *(float*)(addr);
		return fValue;
	}
	return 0;
}

bool Shrek2Memory::WriteInt(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		*(int*)(addr) = iValue;
		return true;
	}
	return false;
}

int Shrek2Memory::ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		int iValue = *(int*)(addr);
		return iValue;
	}
	return 0;
}

bool Shrek2Memory::WriteShortInt(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		*(short int*)(addr) = iValue;
		return true;
	}
	return false;
}

short int Shrek2Memory::ReadShortInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		short int iValue = *(short int*)(addr);
		return iValue;
	}
	return 0;
}

bool Shrek2Memory::WriteBool(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		*(byte*)(addr) = bValue;
		return true;
	}
	return false;
}

bool Shrek2Memory::ReadBool(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
	DWORD addr = GetAddr(shModule, baseAddress, offset1, offset2, offset3, offset4);
	if (addr) {
		byte fValue = *(byte*)(addr);
		return fValue;
	}
	return 0;
}

std::string Shrek2Memory::ReadText(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4)
{
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

DWORD Shrek2Memory::GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4) {
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
/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#pragma once
class Shrek2Memory
{
public:
	static bool WriteFloat(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static float ReadFloat(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteInt(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static int ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1);
	static int ReadInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteShortInt(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static short int ReadShortInt(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteByte(byte bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static byte ReadByte(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteBool(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool ReadBool(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static const char* ReadText(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static char* ReadChar(LPCSTR shModule, DWORD baseAddress, DWORD offset1);
	static DWORD GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static DWORD GetAddr(LPCSTR shModule, DWORD baseAddress, DWORD offset1);

	static bool WriteFloatSafe(float fValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static float ReadFloatSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteIntSafe(int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static int ReadIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1);
	static int ReadIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteShortIntSafe(short int iValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static short int ReadShortIntSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteByteSafe(byte bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static byte ReadByteSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool WriteBoolSafe(bool bValue, LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static bool ReadBoolSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static const char* ReadTextSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static char* ReadCharSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1);
	static DWORD GetAddrSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1, DWORD offset2, DWORD offset3, DWORD offset4);
	static DWORD GetAddrSafe(LPCSTR shModule, DWORD baseAddress, DWORD offset1);
};


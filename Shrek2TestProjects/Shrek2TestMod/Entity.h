#pragma once
#include "Vector.h"

//class Entity
//{
//public:
//	char pad_0000[336]; //0x0000
//	Vector3 Position; //0x0150
//	char pad_015C[520]; //0x015C
//	wchar_t* Name1; //0x0364
//	char pad_0368[488]; //0x0368
//	wchar_t* Name2; //0x0550
//	char pad_0554[2804]; //0x0554
//}; //Size: 0x1048

class Entity
{
public:
	char pad_0000[36]; //0x0000
	void* ClassInfo; //0x0024
	char pad_0028[296]; //0x0028
	Vector3 Position; //0x0150
	char pad_015C[520]; //0x015C
	wchar_t* Name1; //0x0364
	char pad_0368[488]; //0x0368
	wchar_t* Name2; //0x0550
	char pad_0554[756]; //0x0554
}; //Size: 0x0848

class EntityClassInfo
{
public:
	char pad_0000[20]; //0x0000
	int32_t ClassID; //0x0014
	char pad_0018[40]; //0x0018
}; //Size: 0x0040

class CoinCollection
{
public:
	char pad_0000[1084]; //0x0000
	uint32_t Coins; //0x043C
	char pad_0440[1024]; //0x0440
}; //Size: 0x0840
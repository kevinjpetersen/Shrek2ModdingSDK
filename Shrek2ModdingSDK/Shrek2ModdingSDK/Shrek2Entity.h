#pragma once
class Shrek2Entity
{
public:
	char pad_0000[36]; //0x0000
	void* ClassInfo; //0x0024
	char pad_0028[296]; //0x0028
	Shrek2Vector3 Position; //0x0150
	char pad_015C[520]; //0x015C
	wchar_t* Name1; //0x0364
	char pad_0368[488]; //0x0368
	wchar_t* Name2; //0x0550
	char pad_0554[756]; //0x0554
};

class Shrek2EntityClassInfo
{
public:
	char pad_0000[20]; //0x0000
	int32_t ClassID; //0x0014
	char pad_0018[40]; //0x0018
};
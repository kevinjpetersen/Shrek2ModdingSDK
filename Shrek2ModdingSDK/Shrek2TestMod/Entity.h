#pragma once
#include "Vector.h"

class Entity
{
public:
	char pad_0000[336]; //0x0000
	Vector3 Position; //0x0150
	char pad_015C[520]; //0x015C
	wchar_t* Name1; //0x0364
	char pad_0368[488]; //0x0368
	wchar_t* Name2; //0x0550
	char pad_0554[2804]; //0x0554
}; //Size: 0x1048
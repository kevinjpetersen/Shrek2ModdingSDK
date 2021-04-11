#pragma once
class Shrek2AnyCollection
{
public:
	char pad_0000[1084]; //0x0000
	int Items; //0x043C
	char pad_0440[1024]; //0x0440
}; //Size: 0x0840

class Shrek2CoinCollection
{
public:
	char pad_0000[1084]; //0x0000
	uint32_t Coins; //0x043C
	char pad_0440[1024]; //0x0440
}; //Size: 0x0840
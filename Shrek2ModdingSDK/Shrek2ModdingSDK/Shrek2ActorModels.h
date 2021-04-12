#pragma once
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class Shrek2ActorClassInfo
{
public:
	union {
		DEFINE_MEMBER_N(INT32, ClassID, 0x14);
	};
};

class Shrek2Actor
{
public:
	union {
		DEFINE_MEMBER_N(Shrek2ActorClassInfo*, ClassInfo, 0x24);
		DEFINE_MEMBER_N(Shrek2Vector3*, Position, 0x150);
		DEFINE_MEMBER_N(WCHAR*, Name1, 0x364);
		DEFINE_MEMBER_N(WCHAR*, Name2, 0x550);
	};
};

class Shrek2AnyCollection
{
public:
	union {
		DEFINE_MEMBER_N(INT32, Items, 0x43C);
	};
};

class Shrek2CoinCollection
{
public:
	union {
		DEFINE_MEMBER_N(INT32, Coins, 0x43C);
	};
};

class Shrek2ActorCharacter
{
public:
	union {
		DEFINE_MEMBER_N(WCHAR*, Name, 0x364);
		DEFINE_MEMBER_N(Shrek2ActorClassInfo*, ClassInfo, 0x24);
		DEFINE_MEMBER_N(Shrek2Vector3*, Position, 0x150);
		DEFINE_MEMBER_N(Shrek2Vector3*, Velocity, 0x168);
		DEFINE_MEMBER_N(FLOAT, RotationX, 0x15C);
		DEFINE_MEMBER_N(FLOAT, RotationY, 0x160);
		DEFINE_MEMBER_N(FLOAT, RotationZ, 0x164);
		DEFINE_MEMBER_N(FLOAT, VisualScaleAll, 0x268);
	};

	std::string GetName()
	{
		if (!Name) return "";

		std::wstring str = reinterpret_cast<wchar_t*>(Name);
		if (!str.empty())
		{
			return Shrek2Utils::WS2String(str);
		}
		return "";
	}
};
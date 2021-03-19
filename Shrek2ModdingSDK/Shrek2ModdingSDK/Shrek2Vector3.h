#pragma once
class Shrek2Vector3
{
public:
	float X;
	float Y;
	float Z;

	Shrek2Vector3() {}
	Shrek2Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	Shrek2Vector3(float size)
	{
		X = size;
		Y = size;
		Z = size;
	}
};


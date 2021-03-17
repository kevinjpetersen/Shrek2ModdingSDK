#pragma once
class Shrek2Trigger
{
public:
	float X;
	float Y;
	int Size;

	Shrek2Trigger() {}
	Shrek2Trigger(float x, float y, int size)
	{
		X = x;
		Y = y;
		Size = size;
	}

	bool IsInsideTrigger(float x, float y);
};


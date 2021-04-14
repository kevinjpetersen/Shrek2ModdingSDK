/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

bool Shrek2Trigger::IsPositionZero()
{
	try {
		if (Position.X != 0) return false;
		if (Position.Y != 0) return false;
		if (Position.Z != 0) return false;
		return true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Trigger::IsPositionZero", ex.what());
		return false;
	}
}

int Shrek2Trigger::CheckTrigger(std::string name, Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize, bool enableDebugging)
{
	try {
		bool insideTrigger = IsInsideTrigger(valuePosition, valueSize);

		if (insideTrigger)
		{
			if (!Triggered)
			{
				Triggered = true;
				if (enableDebugging)
				{
					std::cout << "Triggered entered '" + name + "' | Type: " + (TriggerOnce ? "TRIGGER_ONCE" : "TRIGGER_EVERY_TIME") << std::endl;
				}
				return 1;
			}
		}
		else
		{
			if (Triggered)
			{
				if (enableDebugging)
				{
					std::cout << "Triggered exited '" + name + "' | Type: " + (TriggerOnce ? "TRIGGER_ONCE" : "TRIGGER_EVERY_TIME") << std::endl;
				}
				if (!TriggerOnce)
				{
					Triggered = false;
					return 0;
				}
				else
				{
					TriggeredOnceExit = true;
					return 0;
				}
			}
		}
		return -1;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Trigger::CheckTrigger", ex.what());
		return -1;
	}
}

bool Shrek2Trigger::IsInsideTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize)
{
	try {
		float aMinX = Position.X - (Size.X / 2);
		float aMaxX = Position.X + (Size.X / 2);
		float aMinY = Position.Y - (Size.Y / 2);
		float aMaxY = Position.Y + (Size.Y / 2);
		float aMinZ = Position.Z - (Size.Z / 2);
		float aMaxZ = Position.Z + (Size.Z / 2);

		float bMinX = valuePosition.X - (valueSize.X);
		float bMaxX = valuePosition.X + (valueSize.X);
		float bMinY = valuePosition.Y - (valueSize.Y);
		float bMaxY = valuePosition.Y + (valueSize.Y);
		float bMinZ = valuePosition.Z - (valueSize.Z);
		float bMaxZ = valuePosition.Z + (valueSize.Z);

		return (aMinX <= bMaxX && aMaxX >= bMinX) &&
			(aMinY <= bMaxY && aMaxY >= bMinY) &&
			(aMinZ <= bMaxZ && aMaxZ >= bMinZ);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Trigger::IsInsideTrigger", ex.what());
		return false;
	}
}
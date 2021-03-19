#include "Shrek2ModdingSDK.h"

int Shrek2Trigger::CheckTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize, bool enableDebugging)
{
	bool insideTrigger = IsInsideTrigger(valuePosition, valueSize);

	if (insideTrigger)
	{
		if (!Triggered)
		{
			Triggered = true;
			if (enableDebugging)
			{
				std::cout << "Triggered entered '" + Name + "' | Type: " + (TriggerOnce ? "TRIGGER_ONCE" : "TRIGGER_EVERY_TIME") << std::endl;
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
				std::cout << "Triggered exited '" + Name + "' | Type: " + (TriggerOnce ? "TRIGGER_ONCE" : "TRIGGER_EVERY_TIME") << std::endl;
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

bool Shrek2Trigger::IsInsideTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize)
{
	float aMinX = Position.X - (Size.X / 2);
	float aMaxX = Position.X + (Size.X / 2);
	float aMinY = Position.Y - (Size.Y / 2);
	float aMaxY = Position.Y + (Size.Y / 2);
	float aMinZ = Position.Z - (Size.Z / 2);
	float aMaxZ = Position.Z + (Size.Z / 2);

	float bMinX = valuePosition.X - (valueSize.X / 2);
	float bMaxX = valuePosition.X + (valueSize.X / 2);
	float bMinY = valuePosition.Y - (valueSize.Y / 2);
	float bMaxY = valuePosition.Y + (valueSize.Y / 2);
	float bMinZ = valuePosition.Z - (valueSize.Z / 2);
	float bMaxZ = valuePosition.Z + (valueSize.Z / 2);

	return (aMinX <= bMaxX && aMaxX >= bMinX) &&
		(aMinY <= bMaxY && aMaxY >= bMinY) &&
		(aMinZ <= bMaxZ && aMaxZ >= bMinZ);
}

Shrek2Vector3 DistanceToTrigger(Shrek2Vector3 value)
{

}
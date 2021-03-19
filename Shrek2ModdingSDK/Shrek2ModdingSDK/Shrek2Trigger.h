#pragma once
class Shrek2Trigger
{
public:
	std::string Name;
	Shrek2Vector3 Position;
	Shrek2Vector3 Size;
	bool Triggered = false;
	bool TriggerOnce = false;
	bool TriggeredOnceExit = false;

	Shrek2Trigger() {}

	Shrek2Trigger(std::string name, Shrek2Vector3 position, Shrek2Vector3 size, bool triggerOnce = false)
	{
		Name = name;
		Position = position;
		Size = size;
		TriggerOnce = triggerOnce;
	}

	int CheckTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize, bool enableDebugging);
	Shrek2Vector3 DistanceToTrigger(Shrek2Vector3 value);
private:
	bool IsInsideTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize);
};


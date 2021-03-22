/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

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
	std::list<Shrek2Maps> TriggeredMaps;
	bool Enabled = true;

	Shrek2Trigger() {}

	Shrek2Trigger(std::string name, Shrek2Vector3 position, Shrek2Vector3 size, Shrek2Maps triggeredMap, bool triggerOnce = false, bool enabled = true)
	{
		Name = name;
		Position = position;
		Size = size;
		TriggeredMaps.push_back(triggeredMap);
		TriggerOnce = triggerOnce;
		Enabled = enabled;
	}

	Shrek2Trigger(std::string name, Shrek2Vector3 position, Shrek2Vector3 size, std::list<Shrek2Maps> triggeredMaps, bool triggerOnce = false, bool enabled = true)
	{
		Name = name;
		Position = position;
		Size = size;
		TriggeredMaps = triggeredMaps;
		TriggerOnce = triggerOnce;
		Enabled = enabled;
	}

	int CheckTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize, bool enableDebugging);
	Shrek2Vector3 DistanceToTrigger(Shrek2Vector3 value);
private:
	bool IsInsideTrigger(Shrek2Vector3 valuePosition, Shrek2Vector3 valueSize);
};


/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

Shrek2Trigger Shrek2Triggers::GetTrigger(std::string name)
{
	if (TriggerExist(name) == false) return Shrek2Trigger();
	return Triggers[name];
}

void Shrek2Triggers::OverwriteTrigger(std::string name, Shrek2Trigger trigger)
{
	if (TriggerExist(name) == false) return;
	Triggers[name] = trigger;
}

void Shrek2Triggers::AddTrigger(std::string name, Shrek2Trigger trigger)
{
	if (TriggerExist(name)) return;
	Triggers.insert(std::pair<std::string, Shrek2Trigger>(name, trigger));
}

void Shrek2Triggers::RemoveTrigger(std::string name)
{
	if (TriggerExist(name) == false) return;
	Triggers.erase(name);
}

void Shrek2Triggers::CheckTriggers(Shrek2Vector3 position, Shrek2Maps currentMap, Shrek2Vector3 currentSize)
{
	for (auto& trigger : Triggers)
	{
		if (!trigger.second.Enabled) continue;

		bool supportsMap = false;

		if (trigger.second.TriggeredMaps.size() > 0)
		{
			for (auto map : trigger.second.TriggeredMaps)
			{
				if (map == currentMap)
				{
					supportsMap = true;
				}
			}
		}
		else {
			supportsMap = true;
		}

		if (supportsMap == false) continue;
		if (trigger.second.Triggered && trigger.second.TriggerOnce && trigger.second.TriggeredOnceExit) continue;

		int triggered = trigger.second.CheckTrigger(trigger.first, position, currentSize, EnableDebugging);
		if (triggered == 1) {
			if(OnTriggerEnter) OnTriggerEnter(trigger.first, trigger.second);
		}
		else if (triggered == 0) {
			if(OnTriggerExit) OnTriggerExit(trigger.first, trigger.second);
		}
	}
}

void Shrek2Triggers::ResetAllTriggers()
{
	for (auto& trigger : Triggers)
	{
		trigger.second.Triggered = false;
		trigger.second.TriggeredOnceExit = false;
		return;
	}
}

void Shrek2Triggers::ResetTrigger(std::string name)
{
	if (TriggerExist(name) == false) return;

	Triggers[name].Triggered = false;
	Triggers[name].TriggeredOnceExit = false;
}

void Shrek2Triggers::EnableTrigger(std::string name)
{
	if (TriggerExist(name) == false) return;

	Triggers[name].Enabled = true;
}

void Shrek2Triggers::DisableTrigger(std::string name)
{
	if (TriggerExist(name) == false) return;

	Triggers[name].Enabled = false;
}

bool Shrek2Triggers::TriggerExist(std::string name)
{
	return Triggers.count(name) > 0;
}


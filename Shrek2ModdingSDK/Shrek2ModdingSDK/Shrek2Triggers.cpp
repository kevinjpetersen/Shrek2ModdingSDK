/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

void Shrek2Triggers::AddTriggers(std::vector<Shrek2Trigger> triggers)
{
	OriginalTriggers = triggers;
	Triggers = triggers;
}

void Shrek2Triggers::CheckTriggers(Shrek2Vector3 position, Shrek2Maps currentMap, Shrek2Vector3 currentSize)
{
	for (int i = 1; i <= Triggers.size(); i++)
	{
		auto trigger = Triggers[i - 1];

		if (!trigger.Enabled) continue;

		bool supportsMap = false;
		for (auto map : trigger.TriggeredMaps)
		{
			if (map == currentMap)
			{
				supportsMap = true;
			}
		}

		if (supportsMap == false) continue;
		if (trigger.Triggered && trigger.TriggerOnce && trigger.TriggeredOnceExit) continue;

		int triggered = trigger.CheckTrigger(position, currentSize, EnableDebugging);
		if (triggered == 1) {
			OnTriggerEnter(trigger);
		}
		else if (triggered == 0) {
			OnTriggerExit(trigger);
		}
		Triggers[i - 1] = trigger;
	}
}

void Shrek2Triggers::ResetAllTriggers()
{
	Triggers = OriginalTriggers;
}

void Shrek2Triggers::ResetTrigger(std::string name)
{
	for (int i = 1; i <= Triggers.size(); i++)
	{
		auto trigger = Triggers[i - 1];
		if (Shrek2Utils::DoesEqual(trigger.Name, name) == false) continue;

		trigger.Triggered = false;
		trigger.TriggeredOnceExit = false;
		Triggers[i - 1] = trigger;
		return;
	}
}

void Shrek2Triggers::EnableTrigger(std::string name)
{
	for (int i = 1; i <= Triggers.size(); i++)
	{
		auto trigger = Triggers[i - 1];
		if (Shrek2Utils::DoesEqual(trigger.Name, name) == false) continue;

		trigger.Enabled = true;
		Triggers[i - 1] = trigger;
		return;
	}
}

void Shrek2Triggers::DisableTrigger(std::string name)
{
	for (int i = 1; i <= Triggers.size(); i++)
	{
		auto trigger = Triggers[i - 1];
		if (Shrek2Utils::DoesEqual(trigger.Name, name) == false) continue;

		trigger.Enabled = false;
		Triggers[i - 1] = trigger;
		return;
	}
}

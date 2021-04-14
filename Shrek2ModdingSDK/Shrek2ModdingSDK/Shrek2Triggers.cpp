/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

Shrek2Trigger Shrek2Triggers::GetTrigger(std::string name)
{
	try {
		if (TriggerExist(name) == false) return Shrek2Trigger();
		return Triggers[name];
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::GetTrigger", ex.what());
		return Shrek2Trigger();
	}
}

void Shrek2Triggers::OverwriteTrigger(std::string name, Shrek2Trigger trigger)
{
	try {
		if (TriggerExist(name) == false) return;
		Triggers[name] = trigger;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::OverwriteTrigger", ex.what());
	}
}

void Shrek2Triggers::AddTrigger(std::string name, Shrek2Trigger trigger)
{
	try {
		if (TriggerExist(name)) return;
		Triggers.insert(std::pair<std::string, Shrek2Trigger>(name, trigger));
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::AddTrigger", ex.what());
	}
}

void Shrek2Triggers::RemoveTrigger(std::string name)
{
	try {
		if (TriggerExist(name) == false) return;
		Triggers.erase(name);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::RemoveTrigger", ex.what());
	}
}

void Shrek2Triggers::CheckTriggers(Shrek2Vector3 position, Shrek2Maps currentMap, Shrek2Vector3 currentSize)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::CheckTriggers", ex.what());
	}
}

void Shrek2Triggers::ResetAllTriggers()
{
	try {
		for (auto& trigger : Triggers)
		{
			trigger.second.Triggered = false;
			trigger.second.TriggeredOnceExit = false;
			return;
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::ResetAllTriggers", ex.what());
	}
}

void Shrek2Triggers::ResetTrigger(std::string name)
{
	try {
		if (TriggerExist(name) == false) return;

		Triggers[name].Triggered = false;
		Triggers[name].TriggeredOnceExit = false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::ResetTrigger", ex.what());
	}
}

void Shrek2Triggers::EnableTrigger(std::string name)
{
	try {
		if (TriggerExist(name) == false) return;

		Triggers[name].Enabled = true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::EnableTrigger", ex.what());
	}
}

void Shrek2Triggers::DisableTrigger(std::string name)
{
	try {
		if (TriggerExist(name) == false) return;

		Triggers[name].Enabled = false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::DisableTrigger", ex.what());
	}
}

bool Shrek2Triggers::TriggerExist(std::string name)
{
	try {
		return Triggers.count(name) > 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Triggers::TriggerExist", ex.what());
	}
}


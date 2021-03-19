#include "Shrek2ModdingSDK.h"

void Shrek2Triggers::AddTrigger(Shrek2Trigger trigger)
{
	Triggers.push_back(trigger);
}

void Shrek2Triggers::CheckTriggers(Shrek2Vector3 position)
{
	for (int i = 1; i <= Triggers.size(); i++)
	{
		auto trigger = Triggers[i - 1];
		if (trigger.Triggered && trigger.TriggerOnce && trigger.TriggeredOnceExit) continue;

		int triggered = trigger.CheckTrigger(position, Shrek2Vector3(100), EnableDebugging);
		if (triggered == 1) {
			OnTriggerEnter(trigger);
		}
		else if (triggered == 0) {
			OnTriggerExit(trigger);
		}
		Triggers[i - 1] = trigger;
	}
}

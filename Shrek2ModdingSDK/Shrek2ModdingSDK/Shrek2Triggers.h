#pragma once
class Shrek2Triggers
{
public:
	void AddTriggers(std::vector<Shrek2Trigger> triggers);
	void CheckTriggers(Shrek2Vector3 position, Shrek2Maps map, Shrek2Vector3 currentSize);
	void ResetAllTriggers();
	void ResetTrigger(std::string name);
	void EnableTrigger(std::string name);
	void DisableTrigger(std::string name);

	bool EnableTriggers = true;
	bool EnableDebugging = false;

	void (*OnTriggerEnter)(Shrek2Trigger trigger);
	void (*OnTriggerExit)(Shrek2Trigger trigger);
private:
	std::vector<Shrek2Trigger> OriginalTriggers;
	std::vector<Shrek2Trigger> Triggers;
};


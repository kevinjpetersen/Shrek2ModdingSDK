#pragma once
class Shrek2Triggers
{
public:
	void AddTrigger(Shrek2Trigger trigger);
	void CheckTriggers(Shrek2Vector3 position);

	bool EnableTriggers = true;
	bool EnableDebugging = false;

	void (*OnTriggerEnter)(Shrek2Trigger trigger);
	void (*OnTriggerExit)(Shrek2Trigger trigger);
private:
	std::vector<Shrek2Trigger> Triggers;
};


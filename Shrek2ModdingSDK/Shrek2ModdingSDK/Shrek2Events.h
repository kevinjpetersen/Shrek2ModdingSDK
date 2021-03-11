#pragma once
class Shrek2Events
{
private:
	// -1 = Reset, 0 = Enter, 1 = Exit
	int IsPlayerInWater = -1;
	int PlayerHealthUpdate = -1;

	// Event Update Functions
	void EU_OnPlayerInWater();
	void EU_OnPlayerHealthUpdate();
public:
	void EventUpdates();

	void (*OnStart)();
	void (*OnTick)();
	void (*OnMapChange)(std::string map); // Fires ONCE when a Map Change is happening
	void (*OnMapChangeDone)(std::string map); // Fires ONCE when the Map Change is done
	void (*OnPlayerHealthUpdate)(); // Fires EVERY TIME the Player's Health changes
	void (*OnPlayerDie)(); // Fires ONCE when the Player dies
	void (*OnPlayerMove)(); // Fires EVERY TIME the Player's Position changes
	void (*OnPlayerRotate)(); // Fires EVERY TIME the Player's Rotation changes
	void (*OnPlayerClimb)(); // Fires ONCE when the Player starts climbing
	void (*OnPlayerClimbDone)(); // Fires ONCE when the Player is done climbing
	void (*OnPlayerInWaterEnter)(); // Fires ONCE when the Player enters the water
	void (*OnPlayerInWaterTick)(); // Fires EVERY TICK when the Player is in the water
	void (*OnPlayerInWaterExit)(); // Fires ONCE when the Player leaves the water
	void (*OnPlayerInAirEnter)(); // Fires ONCE when the Player enters the air
	void (*OnPlayerInAirTick)(); // Fires EVERY TICK when the Player is in the air
	void (*OnPlayerLand)(); // Fires ONCE when the Player lands on the ground
	void (*OnPlayerHitJumpMagnetHit)(); // Fires ONCE when the Player hits a Jump Magnet (Auto Jump)
	void (*OnPlayerHitJumpMagnetDone)(); // Fires ONCE when the Player finishes a Jump Magnet (Auto Jump)
	void (*OnPlayerHitBouncePadHit)(); // Fires ONCE when the Player hits a Bounce Pad
	void (*OnPlayerHitBouncePadDone)(); // Fires ONCE when the Player finishes a Bounce Pad
	void (*OnPlayerMenuOpen)(); // Fires ONCE when the Player opens the Pause Menu
	void (*OnPlayerMenuClose)(); // Fires ONCE when the Player closes the Pause Menu

	// NYI
	void (*OnSave)(); // Fires ONCE when a Save is happening
	void (*OnLoad)(); // Fires ONCE when a Load is happening
	void (*OnCutLogTick)(); // Fires EVERY TICK with new lines of CutLog Data
};


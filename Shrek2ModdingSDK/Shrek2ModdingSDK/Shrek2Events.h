#pragma once
class Shrek2Events
{
private:
	Shrek2Pointers Variables;

	// OnPlayerInWater
	bool IsPlayerInWater = false;

	// OnPlayerHealth
	float OldPlayerHealth = -1;

	// OnPlayerInAir
	bool IsPlayerInAir = false;

	// Event Update Functions
	void EU_OnPlayerInWater();
	void EU_OnPlayerHealthUpdate();
	void EU_OnPlayerInAirLand();
public:
	Shrek2Events() {
		Variables = Shrek2Pointers();
	}
	void EventUpdates();

	void (*OnStart)();
	void (*OnTick)();
	void (*OnMapChange)(std::string map); // Fires ONCE when a Map Change is happening
	void (*OnMapChangeDone)(std::string map); // Fires ONCE when the Map Change is done
	/*DONE*/ void (*OnPlayerHealthUpdate)(float oldHealth, float newHealth); // Fires EVERY TIME the Player's Health changes
	void (*OnPlayerDie)(); // Fires ONCE when the Player dies
	void (*OnPlayerMove)(); // Fires EVERY TIME the Player's Position changes
	void (*OnPlayerRotate)(); // Fires EVERY TIME the Player's Rotation changes
	void (*OnPlayerClimb)(); // Fires ONCE when the Player starts climbing
	void (*OnPlayerClimbDone)(); // Fires ONCE when the Player is done climbing
	/*DONE*/ void (*OnPlayerInWaterEnter)(); // Fires ONCE when the Player enters the water
	/*DONE*/ void (*OnPlayerInWaterTick)(); // Fires EVERY TICK when the Player is in the water
	/*DONE*/ void (*OnPlayerInWaterExit)(); // Fires ONCE when the Player leaves the water
	/*WIP*/ void (*OnPlayerInAirEnter)(); // Fires ONCE when the Player enters the air
	/*WIP*/ void (*OnPlayerInAirTick)(); // Fires EVERY TICK when the Player is in the air
	/*WIP*/ void (*OnPlayerLand)(); // Fires ONCE when the Player lands on the ground
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


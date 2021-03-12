#include "Shrek2ModdingSDK.h"

void Shrek2Events::EU_OnPlayerInWater() {
	if (Variables.GetIsInWater()) {
		if (OnPlayerInWaterTick) OnPlayerInWaterTick();
		if (IsPlayerInWater) return;
		IsPlayerInWater = true;

		if (OnPlayerInWaterEnter) OnPlayerInWaterEnter();
	}
	else
	{
		if (IsPlayerInWater) {
			IsPlayerInWater = false;
			if (OnPlayerInWaterExit) OnPlayerInWaterExit();
		}
	}
}

void Shrek2Events::EU_OnPlayerHealthUpdate()
{
	float playerHealth = Variables.GetPlayerHealth();

	if (OldPlayerHealth == -1) {
		OldPlayerHealth = playerHealth;
	}

	if (playerHealth != OldPlayerHealth) {
		if (OnPlayerHealthUpdate) OnPlayerHealthUpdate(OldPlayerHealth, playerHealth);
		OldPlayerHealth = playerHealth;
	}
}

void Shrek2Events::EU_OnPlayerInAirLand()
{
	if (Variables.GetIsInAir() == 0) {
		if (OnPlayerInAirTick) OnPlayerInAirTick();
		if (IsPlayerInAir) return;
		IsPlayerInAir = true;

		if (OnPlayerInAirEnter) OnPlayerInAirEnter();
	}
	else
	{
		if (IsPlayerInAir) {
			IsPlayerInAir = false;
			if (OnPlayerLand) OnPlayerLand();
		}
	}
}

void Shrek2Events::EventUpdates()
{
	EU_OnPlayerInWater();
	EU_OnPlayerHealthUpdate();
	EU_OnPlayerInAirLand();
}
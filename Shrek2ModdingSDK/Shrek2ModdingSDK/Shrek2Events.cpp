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
		if (OldPlayerHealth == 0 && playerHealth == 100)
		{
			if (OnPlayerRespawn) OnPlayerRespawn();
		}
		if (playerHealth != 0) PlayerDied = false;
		if (playerHealth == 0 && PlayerDied == false) {
			PlayerDied = true;
			if (OnPlayerDie) OnPlayerDie();
		}

		if (OnPlayerHealthUpdate) OnPlayerHealthUpdate(OldPlayerHealth, playerHealth);
		OldPlayerHealth = playerHealth;
	}
}

void Shrek2Events::EU_OnPlayerInAirLand()
{
	if (Variables.GetIsInAir() == 2) {
		if (OnPlayerInAirTick) OnPlayerInAirTick();
		if (IsPlayerInAir) return;
		IsPlayerInAir = true;

		if (OnPlayerInAirEnter) OnPlayerInAirEnter();
	}
	else if(Variables.GetIsInAir() == 1)
	{
		if (IsPlayerInAir) {
			IsPlayerInAir = false;
			if (OnPlayerLand) OnPlayerLand();
		}
	}
}

void Shrek2Events::EU_OnPlayerJumpMagnet()
{
	if (Variables.GetUseJumpMagnet()) {
		if (IsPlayerOnJumpMagnet) return;
		IsPlayerOnJumpMagnet = true;

		if (OnPlayerHitJumpMagnetHit) OnPlayerHitJumpMagnetHit();
	}
	else
	{
		if (IsPlayerOnJumpMagnet) {
			IsPlayerOnJumpMagnet = false;
			if (OnPlayerHitJumpMagnetDone) OnPlayerHitJumpMagnetDone();
		}
	}
}

void Shrek2Events::EU_OnPlayerBouncePad()
{
	if (Variables.GetUseBouncePad()) {
		if (IsPlayerOnBouncePad) return;
		IsPlayerOnBouncePad = true;

		if (OnPlayerHitBouncePadHit) OnPlayerHitBouncePadHit();
	}
	else
	{
		if (IsPlayerOnBouncePad) {
			IsPlayerOnBouncePad = false;
			if (OnPlayerHitBouncePadDone) OnPlayerHitBouncePadDone();
		}
	}
}

void Shrek2Events::EU_OnPlayerInfo()
{
	float posX = Variables.GetPositionX();
	float posY = Variables.GetPositionY();
	float posZ = Variables.GetPositionZ();

	float rotX = Variables.GetRotationX();
	float rotY = Variables.GetRotationY();
	float rotZ = Variables.GetRotationZ();


	if (OldPlayerPositionX == -1) OldPlayerPositionX = posX;
	if (OldPlayerPositionY == -1) OldPlayerPositionY = posY;
	if (OldPlayerPositionZ == -1) OldPlayerPositionZ = posZ;

	if (OldPlayerRotationX == -1) OldPlayerRotationX = rotX;
	if (OldPlayerRotationY == -1) OldPlayerRotationY = rotY;
	if (OldPlayerRotationZ == -1) OldPlayerRotationZ = rotZ;

	if (posX != OldPlayerPositionX || posY != OldPlayerPositionY || posZ != OldPlayerPositionZ) {
		// Position changed
		if (OnPlayerMove) OnPlayerMove(posX, posY, posZ);

		OldPlayerPositionX = posX;
		OldPlayerPositionY = posY;
		OldPlayerPositionZ = posZ;
	}

	if (rotX != OldPlayerRotationX || rotY != OldPlayerRotationY || rotZ != OldPlayerRotationZ) {
		// Rotation changed
		if (abs(rotX - OldPlayerRotationX) > 15 || abs(rotY - OldPlayerRotationY) > 15 || abs(rotZ - OldPlayerRotationZ) > 15) {
			if (OnPlayerRotate) OnPlayerRotate(rotX, rotY, rotZ);
		}

		OldPlayerRotationX = rotX;
		OldPlayerRotationY = rotY;
		OldPlayerRotationZ = rotZ;
	}
}

void Shrek2Events::EventUpdates()
{
	EU_OnPlayerInWater();
	EU_OnPlayerHealthUpdate();
	EU_OnPlayerJumpMagnet();
	EU_OnPlayerBouncePad();
	EU_OnPlayerInAirLand();
	EU_OnPlayerInfo();
}
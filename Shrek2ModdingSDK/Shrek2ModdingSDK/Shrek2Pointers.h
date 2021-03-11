#pragma once
class Shrek2Pointers
{
public:
	bool SetGodMode(bool bGodMode);
	bool GetGodMode();

	bool SetPlayerHealth(float fHealth);
	float GetPlayerHealth();

	bool SetPlayerLocationX(float fValue);
	float GetPlayerLocationX();

	bool SetPlayerLocationY(float fValue);
	float GetPlayerLocationY();

	bool SetPlayerLocationZ(float fValue);
	float GetPlayerLocationZ();

	bool SetPlayerRotationX(short int fValue);
	short int GetPlayerRotationX();

	bool SetPlayerRotationY(short int fValue);
	short int GetPlayerRotationY();

	bool SetPlayerRotationZ(short int fValue);
	short int GetPlayerRotationZ();

	bool SetPlayerAccelerationRate(float fValue);
	float GetPlayerAccelerationRate();

	// CAMERA
	bool SetCameraLocationX(float fValue);
	float GetCameraLocationX();

	bool SetCameraLocationY(float fValue);
	float GetCameraLocationY();

	bool SetCameraLocationZ(float fValue);
	float GetCameraLocationZ();

	bool SetCameraRotationX(short int fValue);
	short int GetCameraRotationX();

	bool SetCameraRotationY(short int fValue);
	short int GetCameraRotationY();

	bool SetCameraRotationZ(short int fValue);
	short int GetCameraRotationZ();

	float GetCameraAngleX();
	float GetCameraAngleY();
	float GetCameraAngleZ();

	std::string GetCurrentMap();

	// OVERALL CAMERA ROTATION
	bool SetCameraRotation(short int fValue);
	short int GetCameraRotation();
};


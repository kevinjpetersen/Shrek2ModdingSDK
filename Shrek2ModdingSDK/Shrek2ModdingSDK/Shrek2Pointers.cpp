#include "Shrek2ModdingSDK.h"

// PLAYER

bool Shrek2Pointers::SetGodMode(bool bGodMode) {
	return Shrek2Memory::WriteBool(bGodMode, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x14A0);
}
bool Shrek2Pointers::GetGodMode() {
	return Shrek2Memory::ReadBool("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x14A0);
}

bool Shrek2Pointers::SetPlayerHealth(float fHealth) {
	return Shrek2Memory::WriteFloat(fHealth, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x4E0);
}
float Shrek2Pointers::GetPlayerHealth() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x4E0);
}

bool Shrek2Pointers::SetPlayerLocationX(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x150);
}
float Shrek2Pointers::GetPlayerLocationX() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x150);
}

bool Shrek2Pointers::SetPlayerLocationY(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x154);
}
float Shrek2Pointers::GetPlayerLocationY() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x154);
}

bool Shrek2Pointers::SetPlayerLocationZ(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x158);
}
float Shrek2Pointers::GetPlayerLocationZ() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x158);
}

bool Shrek2Pointers::SetPlayerRotationX(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x15C);
}
short int Shrek2Pointers::GetPlayerRotationX() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x15C);
}

bool Shrek2Pointers::SetPlayerRotationY(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x160);
}
short int Shrek2Pointers::GetPlayerRotationY() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x160);
}

bool Shrek2Pointers::SetPlayerRotationZ(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x164);
}
short int Shrek2Pointers::GetPlayerRotationZ() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x164);
}

bool Shrek2Pointers::SetPlayerAccelerationRate(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x478);
}
float Shrek2Pointers::GetPlayerAccelerationRate() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x68, 0x9C, 0x664, 0x478);
}

// CAMERA

bool Shrek2Pointers::SetCameraLocationX(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x150);
}
float Shrek2Pointers::GetCameraLocationX() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x150);
}

bool Shrek2Pointers::SetCameraLocationY(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x154);
}
float Shrek2Pointers::GetCameraLocationY() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x154);
}

bool Shrek2Pointers::SetCameraLocationZ(float fValue) {
	return Shrek2Memory::WriteFloat(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x158);
}
float Shrek2Pointers::GetCameraLocationZ() {
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x158);
}

bool Shrek2Pointers::SetCameraRotationX(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x15C);
}
short int Shrek2Pointers::GetCameraRotationX() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x15C);
}

bool Shrek2Pointers::SetCameraRotationY(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x160);
}
short int Shrek2Pointers::GetCameraRotationY() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x160);
}

bool Shrek2Pointers::SetCameraRotationZ(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x164);
}
short int Shrek2Pointers::GetCameraRotationZ() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x164);
}

float Shrek2Pointers::GetCameraAngleX()
{
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x1080);
}

float Shrek2Pointers::GetCameraAngleY()
{
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x1084);
}

float Shrek2Pointers::GetCameraAngleZ()
{
	return Shrek2Memory::ReadFloat("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x1088);
}

std::string Shrek2Pointers::GetCurrentMap()
{
	return Shrek2Memory::ReadText("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0xA8, 0x4E0);
}

bool Shrek2Pointers::SetCameraRotation(short int fValue) {
	return Shrek2Memory::WriteShortInt(fValue, "Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x109C);
}
short int Shrek2Pointers::GetCameraRotation() {
	return Shrek2Memory::ReadShortInt("Engine.dll", 0x4DFFF8, 0x30, 0x34, 0x898, 0x109C);
}
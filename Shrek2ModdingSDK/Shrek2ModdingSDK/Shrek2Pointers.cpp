/*
    Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

bool Shrek2Pointers::SetPlayerHealth(float PlayerHealth) {
    return Shrek2Memory::WriteFloat(PlayerHealth, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4E0);
}
float Shrek2Pointers::GetPlayerHealth() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4E0);
}

bool Shrek2Pointers::SetPositionX(float PositionX) {
    return Shrek2Memory::WriteFloat(PositionX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x150);
}
float Shrek2Pointers::GetPositionX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x150);
}

bool Shrek2Pointers::SetPositionY(float PositionY) {
    return Shrek2Memory::WriteFloat(PositionY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x154);
}
float Shrek2Pointers::GetPositionY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x154);
}

bool Shrek2Pointers::SetPositionZ(float PositionZ) {
    return Shrek2Memory::WriteFloat(PositionZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x158);
}
float Shrek2Pointers::GetPositionZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x158);
}

bool Shrek2Pointers::SetPosition(Shrek2Vector3 position) {
    bool success = true;
    success = SetPositionX(position.X);
    success = SetPositionY(position.Y);
    success = SetPositionZ(position.Z);
    return success;
}
Shrek2Vector3 Shrek2Pointers::GetPosition() {
    return Shrek2Vector3(GetPositionX(), GetPositionY(), GetPositionZ());
}

bool Shrek2Pointers::SetVelocityX(float VelocityX) {
    return Shrek2Memory::WriteFloat(VelocityX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x168);
}
float Shrek2Pointers::GetVelocityX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x168);
}

bool Shrek2Pointers::SetVelocityY(float VelocityY) {
    return Shrek2Memory::WriteFloat(VelocityY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x16C);
}
float Shrek2Pointers::GetVelocityY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x16C);
}

bool Shrek2Pointers::SetVelocityZ(float VelocityZ) {
    return Shrek2Memory::WriteFloat(VelocityZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x170);
}
float Shrek2Pointers::GetVelocityZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x170);
}

bool Shrek2Pointers::SetRotationX(short int RotationX) {
    return Shrek2Memory::WriteShortInt(RotationX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x15C);
}
short int Shrek2Pointers::GetRotationX() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x15C);
}

bool Shrek2Pointers::SetRotationY(short int RotationY) {
    return Shrek2Memory::WriteShortInt(RotationY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x160);
}
short int Shrek2Pointers::GetRotationY() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x160);
}

bool Shrek2Pointers::SetRotationZ(short int RotationZ) {
    return Shrek2Memory::WriteShortInt(RotationZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x164);
}
short int Shrek2Pointers::GetRotationZ() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x164);
}

bool Shrek2Pointers::SetGodMode(bool GodMode) {
    return Shrek2Memory::WriteBool(GodMode, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14A0);
}
bool Shrek2Pointers::GetGodMode() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14A0);
}

bool Shrek2Pointers::SetFatalFallDistance(int FatalFallDistance) {
    return Shrek2Memory::WriteInt(FatalFallDistance, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x149C);
}
int Shrek2Pointers::GetFatalFallDistance() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x149C);
}

bool Shrek2Pointers::SetShrink(bool Shrink) {
    return Shrek2Memory::WriteBool(Shrink, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1500);
}
bool Shrek2Pointers::GetShrink() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1500);
}

bool Shrek2Pointers::SetInvisible(bool Invisible) {
    return Shrek2Memory::WriteBool(Invisible, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14D0);
}
bool Shrek2Pointers::GetInvisible() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14D0);
}

bool Shrek2Pointers::SetInvisibilityPercent(float InvisibilityPercent) {
    return Shrek2Memory::WriteFloat(InvisibilityPercent, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14D8);
}
float Shrek2Pointers::GetInvisibilityPercent() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14D8);
}

bool Shrek2Pointers::SetHasStrengthPotion(bool HasStrengthPotion) {
    return Shrek2Memory::WriteBool(HasStrengthPotion, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14DC);
}
bool Shrek2Pointers::GetHasStrengthPotion() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14DC);
}

bool Shrek2Pointers::SetStrengthPotionScale(int StrengthPotionScale) {
    return Shrek2Memory::WriteInt(StrengthPotionScale, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14FC);
}
int Shrek2Pointers::GetStrengthPotionScale() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14FC);
}

bool Shrek2Pointers::SetShrinkSpeed(float ShrinkSpeed) {
    return Shrek2Memory::WriteFloat(ShrinkSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1508);
}
float Shrek2Pointers::GetShrinkSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1508);
}

bool Shrek2Pointers::SetShrinkLimit(float ShrinkLimit) {
    return Shrek2Memory::WriteFloat(ShrinkLimit, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x150C);
}
float Shrek2Pointers::GetShrinkLimit() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x150C);
}

bool Shrek2Pointers::SetPotionScale(float PotionScale) {
    return Shrek2Memory::WriteFloat(PotionScale, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1510);
}
float Shrek2Pointers::GetPotionScale() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1510);
}

bool Shrek2Pointers::SetUseJumpMagnet(bool UseJumpMagnet) {
    return Shrek2Memory::WriteByte(UseJumpMagnet ? 17 : 1, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14B4);
}
bool Shrek2Pointers::GetUseJumpMagnet() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14B4);
    return localByte == 17 ? true : false;
}

bool Shrek2Pointers::SetUseBouncePad(bool UseBouncePad) {
    return Shrek2Memory::WriteByte(UseBouncePad ? 9 : 1, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14B4);
}
bool Shrek2Pointers::GetUseBouncePad() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x14B4);
    return localByte == 9 ? true : false;
}

bool Shrek2Pointers::SetKnockBackDistance(float KnockBackDistance) {
    return Shrek2Memory::WriteFloat(KnockBackDistance, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1480);
}
float Shrek2Pointers::GetKnockBackDistance() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1480);
}

bool Shrek2Pointers::SetJumpAttackFallSpeed(float JumpAttackFallSpeed) {
    return Shrek2Memory::WriteFloat(JumpAttackFallSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1290);
}
float Shrek2Pointers::GetJumpAttackFallSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1290);
}

bool Shrek2Pointers::SetJumpAttackBoostHeight(float JumpAttackBoostHeight) {
    return Shrek2Memory::WriteFloat(JumpAttackBoostHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x128C);
}
float Shrek2Pointers::GetJumpAttackBoostHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x128C);
}

bool Shrek2Pointers::SetJumpAttackToggle(bool JumpAttackToggle) {
    return Shrek2Memory::WriteBool(JumpAttackToggle, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1278);
}
bool Shrek2Pointers::GetJumpAttackToggle() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1278);
}

bool Shrek2Pointers::SetMaxCombatants(int MaxCombatants) {
    return Shrek2Memory::WriteInt(MaxCombatants, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1214);
}
int Shrek2Pointers::GetMaxCombatants() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1214);
}

int Shrek2Pointers::GetNumberofCombatants() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1210);
}

bool Shrek2Pointers::SetKnockbackToggle(bool KnockbackToggle) {
    return Shrek2Memory::WriteByte(KnockbackToggle ? 2 : 0, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1208);
}
bool Shrek2Pointers::GetKnockbackToggle() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1208);
    return localByte == 2 ? true : false;
}

bool Shrek2Pointers::SetSayCombatDialog(bool SayCombatDialog) {
    return Shrek2Memory::WriteBool(SayCombatDialog, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x120C);
}
bool Shrek2Pointers::GetSayCombatDialog() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x120C);
}

bool Shrek2Pointers::SetAttackMoveAhead(float AttackMoveAhead) {
    return Shrek2Memory::WriteFloat(AttackMoveAhead, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11D0);
}
float Shrek2Pointers::GetAttackMoveAhead() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11D0);
}

bool Shrek2Pointers::SetJumpAttackMoveAhead(float JumpAttackMoveAhead) {
    return Shrek2Memory::WriteFloat(JumpAttackMoveAhead, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11D4);
}
float Shrek2Pointers::GetJumpAttackMoveAhead() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11D4);
}

bool Shrek2Pointers::SetFrontEndPlayer(bool FrontEndPlayer) {
    return Shrek2Memory::WriteBool(FrontEndPlayer, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11CC);
}
bool Shrek2Pointers::GetFrontEndPlayer() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x11CC);
}

bool Shrek2Pointers::SetBaseEyeHeight(float BaseEyeHeight) {
    return Shrek2Memory::WriteFloat(BaseEyeHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4B8);
}
float Shrek2Pointers::GetBaseEyeHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4B8);
}

float Shrek2Pointers::GetEyeHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x4BC);
}

bool Shrek2Pointers::SetCollisionHeight(float CollisionHeight) {
    return Shrek2Memory::WriteFloat(CollisionHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2E0);
}
float Shrek2Pointers::GetCollisionHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2E0);
}

bool Shrek2Pointers::SetCollisionRadius(float CollisionRadius) {
    return Shrek2Memory::WriteFloat(CollisionRadius, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2D8);
}
float Shrek2Pointers::GetCollisionRadius() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2D8);
}

bool Shrek2Pointers::SetDoubleJumpHeight(float DoubleJumpHeight) {
    return Shrek2Memory::WriteFloat(DoubleJumpHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0xEFC);
}
float Shrek2Pointers::GetDoubleJumpHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0xEFC);
}

bool Shrek2Pointers::SetJumpHeight(float JumpHeight) {
    return Shrek2Memory::WriteFloat(JumpHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x47C);
}
float Shrek2Pointers::GetJumpHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x47C);
}

bool Shrek2Pointers::SetMaxSlopeAngle(float MaxSlopeAngle) {
    return Shrek2Memory::WriteFloat(MaxSlopeAngle, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x49C);
}
float Shrek2Pointers::GetMaxSlopeAngle() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x49C);
}

bool Shrek2Pointers::GetIsClimbing() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0xEBC);
    return localByte == 1 ? true : false;
}

int Shrek2Pointers::GetIsInAir() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5A8);
}

bool Shrek2Pointers::GetIsInGhost() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5A8) == 4 ? true : false;
}

bool Shrek2Pointers::GetIsBigMount() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5A8) == 6 ? true : false;
}

bool Shrek2Pointers::GetIsLadderOrShimmeyPipe() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5A8) == 11 ? true : false;
}

bool Shrek2Pointers::SetMovementAnimationSpeed(float MovementAnimationSpeed) {
    return Shrek2Memory::WriteFloat(MovementAnimationSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5BC);
}
float Shrek2Pointers::GetMovementAnimationSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5BC);
}

bool Shrek2Pointers::SetMovementAnimationTransitionSpeed(float MovementAnimationTransitionSpeed) {
    return Shrek2Memory::WriteFloat(MovementAnimationTransitionSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5D8);
}
float Shrek2Pointers::GetMovementAnimationTransitionSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5D8);
}

bool Shrek2Pointers::SetMovementSpeed(float MovementSpeed) {
    return Shrek2Memory::WriteFloat(MovementSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0xB40);
}
float Shrek2Pointers::GetMovementSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0xB40);
}

bool Shrek2Pointers::SetCurrentMovementSpeed(float CurrentMovementSpeed) {
    return Shrek2Memory::WriteFloat(CurrentMovementSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x468);
}
float Shrek2Pointers::GetCurrentMovementSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x468);
}

bool Shrek2Pointers::SetTurningSpeed(int TurningSpeed) {
    return Shrek2Memory::WriteInt(TurningSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x314);
}
int Shrek2Pointers::GetTurningSpeed() {
    return Shrek2Memory::ReadInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x314);
}

bool Shrek2Pointers::SetAmbientGlow(bool AmbientGlow) {
    return Shrek2Memory::WriteBool(AmbientGlow, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x294);
}
bool Shrek2Pointers::GetAmbientGlow() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x294);
}

bool Shrek2Pointers::SetUnlit(bool Unlit) {
    return Shrek2Memory::WriteByte(Unlit ? 129 : 128, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2BC);
}
bool Shrek2Pointers::GetUnlit() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x2BC);
    return localByte == 129 ? true : false;
}

bool Shrek2Pointers::SetVisualScale(float VisualScale) {
    return Shrek2Memory::WriteFloat(VisualScale, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x268);
}
float Shrek2Pointers::GetVisualScale() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x268);
}

bool Shrek2Pointers::SetVisualScaleX(float VisualScaleX) {
    return Shrek2Memory::WriteFloat(VisualScaleX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x26C);
}
float Shrek2Pointers::GetVisualScaleX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x26C);
}

bool Shrek2Pointers::SetVisualScaleY(float VisualScaleY) {
    return Shrek2Memory::WriteFloat(VisualScaleY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x270);
}
float Shrek2Pointers::GetVisualScaleY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x270);
}

bool Shrek2Pointers::SetVisualScaleZ(float VisualScaleZ) {
    return Shrek2Memory::WriteFloat(VisualScaleZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x274);
}
float Shrek2Pointers::GetVisualScaleZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x274);
}

bool Shrek2Pointers::SetPrePivotX(float PrePivotX) {
    return Shrek2Memory::WriteFloat(PrePivotX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x278);
}
float Shrek2Pointers::GetPrePivotX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x278);
}

bool Shrek2Pointers::SetPrePivotY(float PrePivotY) {
    return Shrek2Memory::WriteFloat(PrePivotY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x27C);
}
float Shrek2Pointers::GetPrePivotY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x27C);
}

bool Shrek2Pointers::SetPrePivotZ(float PrePivotZ) {
    return Shrek2Memory::WriteFloat(PrePivotZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x280);
}
float Shrek2Pointers::GetPrePivotZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x280);
}

bool Shrek2Pointers::SetResetRotation(bool ResetRotation) {
    return Shrek2Memory::WriteByte(ResetRotation ? 2 : 1, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x400);
}
bool Shrek2Pointers::GetResetRotation() {
    byte localByte = Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x400);
    return localByte == 2 ? true : false;
}

bool Shrek2Pointers::GetIsInWater() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1084);
}

bool Shrek2Pointers::SetWaterSpeed(float WaterSpeed) {
    return Shrek2Memory::WriteFloat(WaterSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1088);
}
float Shrek2Pointers::GetWaterSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1088);
}

bool Shrek2Pointers::SetWaterSpeed2(float WaterSpeed2) {
    return Shrek2Memory::WriteFloat(WaterSpeed2, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x46C);
}
float Shrek2Pointers::GetWaterSpeed2() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x46C);
}

bool Shrek2Pointers::SetNoclipSpeed(float NoclipSpeed) {
    return Shrek2Memory::WriteFloat(NoclipSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x470);
}
float Shrek2Pointers::GetNoclipSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x470);
}

bool Shrek2Pointers::SetLadderSpeed(float LadderSpeed) {
    return Shrek2Memory::WriteFloat(LadderSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x474);
}
float Shrek2Pointers::GetLadderSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x474);
}

bool Shrek2Pointers::SetAccelerationRate(float AccelerationRate) {
    return Shrek2Memory::WriteFloat(AccelerationRate, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x478);
}
float Shrek2Pointers::GetAccelerationRate() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x478);
}

bool Shrek2Pointers::SetAirControl(float AirControl) {
    return Shrek2Memory::WriteFloat(AirControl, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x480);
}
float Shrek2Pointers::GetAirControl() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x480);
}

bool Shrek2Pointers::SetAttackDistance(float AttackDistance) {
    return Shrek2Memory::WriteFloat(AttackDistance, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x109C);
}
float Shrek2Pointers::GetAttackDistance() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x109C);
}

bool Shrek2Pointers::SetAttackHeight(float AttackHeight) {
    return Shrek2Memory::WriteFloat(AttackHeight, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A0);
}
float Shrek2Pointers::GetAttackHeight() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A0);
}

bool Shrek2Pointers::SetAttackAngle(float AttackAngle) {
    return Shrek2Memory::WriteFloat(AttackAngle, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A4);
}
float Shrek2Pointers::GetAttackAngle() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A4);
}

bool Shrek2Pointers::SetSpecialAttackTime(float SpecialAttackTime) {
    return Shrek2Memory::WriteFloat(SpecialAttackTime, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A8);
}
float Shrek2Pointers::GetSpecialAttackTime() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x10A8);
}

bool Shrek2Pointers::SetTerminalVelocity(float TerminalVelocity) {
    return Shrek2Memory::WriteFloat(TerminalVelocity, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x488);
}
float Shrek2Pointers::GetTerminalVelocity() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x488);
}

bool Shrek2Pointers::SetFriction(float Friction) {
    return Shrek2Memory::WriteFloat(Friction, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x484);
}
float Shrek2Pointers::GetFriction() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x484);
}

bool Shrek2Pointers::SetInGameTimer(float InGameTimer) {
    return Shrek2Memory::WriteFloat(InGameTimer, "Engine.dll", 0x004DFFF8, 0x68, 0x14C, 0x9C, 0x480);
}
float Shrek2Pointers::GetInGameTimer() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x14C, 0x9C, 0x480);
}

bool Shrek2Pointers::SetGravityX(float GravityX) {
    return Shrek2Memory::WriteFloat(GravityX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x478);
}
float Shrek2Pointers::GetGravityX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x478);
}

bool Shrek2Pointers::SetGravityY(float GravityY) {
    return Shrek2Memory::WriteFloat(GravityY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x47C);
}
float Shrek2Pointers::GetGravityY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x47C);
}

bool Shrek2Pointers::SetGravityZ(float GravityZ) {
    return Shrek2Memory::WriteFloat(GravityZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x480);
}
float Shrek2Pointers::GetGravityZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x14C, 0x480);
}

bool Shrek2Pointers::SetGameSpeed(float GameSpeed) {
    return Shrek2Memory::WriteFloat(GameSpeed, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0xA8, 0x47C);
}
float Shrek2Pointers::GetGameSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0xA8, 0x47C);
}

bool Shrek2Pointers::SetChangeTo0ToCrash(float ChangeTo0ToCrash) {
    return Shrek2Memory::WriteFloat(ChangeTo0ToCrash, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x308);
}
float Shrek2Pointers::GetChangeTo0ToCrash() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x308);
}

bool Shrek2Pointers::SetCamPositionX(float CamPositionX) {
    return Shrek2Memory::WriteFloat(CamPositionX, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A4);
}
float Shrek2Pointers::GetCamPositionX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A4);
}

bool Shrek2Pointers::SetCamPositionY(float CamPositionY) {
    return Shrek2Memory::WriteFloat(CamPositionY, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A8);
}
float Shrek2Pointers::GetCamPositionY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A8);
}

bool Shrek2Pointers::SetCamPositionZ(float CamPositionZ) {
    return Shrek2Memory::WriteFloat(CamPositionZ, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10AC);
}
float Shrek2Pointers::GetCamPositionZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10AC);
}

bool Shrek2Pointers::SetCamRotationX(short int CamRotationX) {
    return Shrek2Memory::WriteShortInt(CamRotationX, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1098);
}
short int Shrek2Pointers::GetCamRotationX() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1098);
}

bool Shrek2Pointers::SetCamRotationY(short int CamRotationY) {
    return Shrek2Memory::WriteShortInt(CamRotationY, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x109C);
}
short int Shrek2Pointers::GetCamRotationY() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x109C);
}

bool Shrek2Pointers::SetCamRotationZ(short int CamRotationZ) {
    return Shrek2Memory::WriteShortInt(CamRotationZ, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A0);
}
short int Shrek2Pointers::GetCamRotationZ() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10A0);
}

bool Shrek2Pointers::SetDesiredLookDistance(float DesiredLookDistance) {
    return Shrek2Memory::WriteFloat(DesiredLookDistance, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10CC);
}
float Shrek2Pointers::GetDesiredLookDistance() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10CC);
}

bool Shrek2Pointers::SetCamSmoothing(float CamSmoothing) {
    return Shrek2Memory::WriteFloat(CamSmoothing, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10F4);
}
float Shrek2Pointers::GetCamSmoothing() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10F4);
}

bool Shrek2Pointers::SetCamSensitivity(float CamSensitivity) {
    return Shrek2Memory::WriteFloat(CamSensitivity, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10F8);
}
float Shrek2Pointers::GetCamSensitivity() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x10F8);
}

bool Shrek2Pointers::SetCamHorizontalSpeed(float CamHorizontalSpeed) {
    return Shrek2Memory::WriteFloat(CamHorizontalSpeed, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1100);
}
float Shrek2Pointers::GetCamHorizontalSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1100);
}

bool Shrek2Pointers::SetCamVerticalSpeed(float CamVerticalSpeed) {
    return Shrek2Memory::WriteFloat(CamVerticalSpeed, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1104);
}
float Shrek2Pointers::GetCamVerticalSpeed() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1104);
}

bool Shrek2Pointers::SetCamHorizontalSensitivity(float CamHorizontalSensitivity) {
    return Shrek2Memory::WriteFloat(CamHorizontalSensitivity, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x110C);
}
float Shrek2Pointers::GetCamHorizontalSensitivity() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x110C);
}

bool Shrek2Pointers::SetCamVerticalSensitivity(float CamVerticalSensitivity) {
    return Shrek2Memory::WriteFloat(CamVerticalSensitivity, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1110);
}
float Shrek2Pointers::GetCamVerticalSensitivity() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1110);
}

bool Shrek2Pointers::SetCamMinimumPitch(float CamMinimumPitch) {
    return Shrek2Memory::WriteFloat(CamMinimumPitch, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1114);
}
float Shrek2Pointers::GetCamMinimumPitch() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1114);
}

bool Shrek2Pointers::SetCamMaximumPitch(float CamMaximumPitch) {
    return Shrek2Memory::WriteFloat(CamMaximumPitch, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1118);
}
float Shrek2Pointers::GetCamMaximumPitch() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1118);
}

bool Shrek2Pointers::SetCamCollisionToggle(bool CamCollisionToggle) {
    return Shrek2Memory::WriteBool(CamCollisionToggle, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1078);
}
bool Shrek2Pointers::GetCamCollisionToggle() {
    return Shrek2Memory::ReadBool("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1078);
}

bool Shrek2Pointers::SetDonkeySwampPositionX(float DonkeySwampPositionX) {
    return Shrek2Memory::WriteFloat(DonkeySwampPositionX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1950);
}
float Shrek2Pointers::GetDonkeySwampPositionX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1950);
}

bool Shrek2Pointers::SetDonkeySwampPositionY(float DonkeySwampPositionY) {
    return Shrek2Memory::WriteFloat(DonkeySwampPositionY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1954);
}
float Shrek2Pointers::GetDonkeySwampPositionY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1954);
}

bool Shrek2Pointers::SetDonkeySwampPositionZ(float DonkeySwampPositionZ) {
    return Shrek2Memory::WriteFloat(DonkeySwampPositionZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1958);
}
float Shrek2Pointers::GetDonkeySwampPositionZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x1958);
}

std::string Shrek2Pointers::GetCurrentMap()
{
    wchar_t* t = Shrek2Memory::ReadText("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0xA8, 0x4E0);
    if (t)
    {
        return Shrek2Utils::WS2String(t);
    }
    return "";
}

std::string Shrek2Pointers::GetCurrentCharacter()
{
    wchar_t* t = Shrek2Memory::ReadText("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x550);
    if (t)
    {
        return Shrek2Utils::WS2String(t);
    }
    return "";
}

bool Shrek2Pointers::SetRotationRateX(short int RotationRateX) {
    return Shrek2Memory::WriteShortInt(RotationRateX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x310);
}
short int Shrek2Pointers::GetRotationRateX() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x310);
}

bool Shrek2Pointers::SetRotationRateY(short int RotationRateY) {
    return Shrek2Memory::WriteShortInt(RotationRateY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x318);
}
short int Shrek2Pointers::GetRotationRateY() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x318);
}

bool Shrek2Pointers::SetRotationRateZ(short int RotationRateZ) {
    return Shrek2Memory::WriteShortInt(RotationRateZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x314);
}
short int Shrek2Pointers::GetRotationRateZ() {
    return Shrek2Memory::ReadShortInt("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x314);
}

bool Shrek2Pointers::SetFOV(float FOV) {
    return Shrek2Memory::WriteFloat(FOV, "Engine.dll", 0x004DFFF8, 0x30, 0xD8, 0x34, 0x604);
}
float Shrek2Pointers::GetFOV() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0xD8, 0x34, 0x604);
}

bool Shrek2Pointers::SetAccelerationX(float AccelerationX) {
    return Shrek2Memory::WriteFloat(AccelerationX, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B0);
}
float Shrek2Pointers::GetAccelerationX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B0);
}

bool Shrek2Pointers::SetAccelerationY(float AccelerationY) {
    return Shrek2Memory::WriteFloat(AccelerationY, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B4);
}
float Shrek2Pointers::GetAccelerationY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B4);
}

bool Shrek2Pointers::SetAccelerationZ(float AccelerationZ) {
    return Shrek2Memory::WriteFloat(AccelerationZ, "Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B8);
}
float Shrek2Pointers::GetAccelerationZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x68, 0x9C, 0x664, 0x5B8);
}

float Shrek2Pointers::GetCamAngleX() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1080);
}

float Shrek2Pointers::GetCamAngleY() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1084);
}

float Shrek2Pointers::GetCamAngleZ() {
    return Shrek2Memory::ReadFloat("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1088);
}

bool Shrek2Pointers::SetCameraBehavior_LockCameraLook()
{
    return Shrek2Memory::WriteByte(3, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1070);
}

bool Shrek2Pointers::SetCameraBehavior_LockCameraMovement()
{
    return Shrek2Memory::WriteByte(0, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1070);
}

bool Shrek2Pointers::SetCameraBehavior_LockCameraMovementAndLook()
{
    return Shrek2Memory::WriteByte(1, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1070);
}

bool Shrek2Pointers::SetCameraBehavior_Normal()
{
    return Shrek2Memory::WriteByte(2, "Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1070);
}

int Shrek2Pointers::GetCameraBehavior()
{
    return Shrek2Memory::ReadByte("Engine.dll", 0x004DFFF8, 0x30, 0x34, 0x898, 0x1070);
}

std::string Shrek2Pointers::GetCurrentConsoleCommand()
{
    wchar_t* t = Shrek2Memory::ReadText("Engine.dll", 0x004E85F0, 0x18C, 0x254, 0x2C8);
    if (t)
    {
        return Shrek2Utils::WS2String(t);
    }
    return "";
}

bool Shrek2Pointers::GetIsConsoleOpen()
{
    int v = Shrek2Memory::ReadInt("Engine.dll", 0x004E85F0, 0x18C, 0x254, 0x394);
    return v == 0 ? false : true;
}
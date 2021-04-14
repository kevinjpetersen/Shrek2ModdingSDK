#include "Shrek2ModdingSDK.h"

int Shrek2Inventory::GetCoins()
{
	return GetInventoryItem(Shrek2CollectionTypes::CoinCollection);
}

int Shrek2Inventory::GetShamrocks()
{
	return GetInventoryItem(Shrek2CollectionTypes::ShamrockCollection);
}

int Shrek2Inventory::GetStrengthPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::StrengthPotionCollection);
}

int Shrek2Inventory::GetShrinkPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::ShrinkPotionCollection);
}

int Shrek2Inventory::GetInvisibilityPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::InvisibilityPotionCollection);
}

int Shrek2Inventory::GetSleepPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::SleepPotionCollection);
}

int Shrek2Inventory::GetStinkPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::StinkPotionCollection);
}

int Shrek2Inventory::GetShrinkEnemeyPotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::ShrinkEnemeyPotionCollection);
}

int Shrek2Inventory::GetFreezePotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::FreezePotionCollection);
}

int Shrek2Inventory::GetLovePotions()
{
	return GetInventoryItem(Shrek2CollectionTypes::LovePotionCollection);
}

void Shrek2Inventory::SetCoins(int newValue)
{
	try {
		bool wasSet = SetInventoryItem(Shrek2CollectionTypes::CoinCollection, newValue);
		if (!wasSet)
		{
			Shrek2::Instance->Functions.CC("addcoins " + std::to_string(newValue));
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Inventory::SetCoins", ex.what());
	}
}

void Shrek2Inventory::SetShamrocks(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::ShamrockCollection, newValue);
}

void Shrek2Inventory::SetStrengthPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::StrengthPotionCollection, newValue);
}

void Shrek2Inventory::SetShrinkPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::ShrinkPotionCollection, newValue);
}

void Shrek2Inventory::SetInvisibilityPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::InvisibilityPotionCollection, newValue);
}

void Shrek2Inventory::SetSleepPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::SleepPotionCollection, newValue);
}

void Shrek2Inventory::SetStinkPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::StinkPotionCollection, newValue);
}

void Shrek2Inventory::SetShrinkEnemeyPotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::ShrinkEnemeyPotionCollection, newValue);
}

void Shrek2Inventory::SetFreezePotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::FreezePotionCollection, newValue);
}

void Shrek2Inventory::SetLovePotions(int newValue)
{
	SetInventoryItem(Shrek2CollectionTypes::LovePotionCollection, newValue);
}

int Shrek2Inventory::GetInventoryItem(Shrek2CollectionTypes itemType)
{
	try {
		auto collection1 = Shrek2ActorList::GetCollection(itemType);
		if (collection1 != NULL) {
			return collection1->Items;
		}
		return 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Inventory::GetInventoryItem", ex.what());
		return 0;
	}
}

bool Shrek2Inventory::SetInventoryItem(Shrek2CollectionTypes itemType, int newValue)
{
	try {
		auto collection1 = Shrek2ActorList::GetCollection(itemType);

		if (collection1 != NULL) {
			if (collection1->Items)
			{
				collection1->Items = newValue;
				return true;
			}
		}
		return false;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Inventory::SetInventoryItem", ex.what());
		return false;
	}
}

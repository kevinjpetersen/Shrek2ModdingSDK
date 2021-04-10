#include "Shrek2ModdingSDK.h"

std::vector<Shrek2Entity*> Shrek2EntityList::GetEntities(Shrek2EntityTypes entityType)
{
	auto entities = FindEntities();
	if (entities.empty()) return {};

	std::vector<Shrek2Entity*> ents = {};

	Shrek2EntityClassInfo* classInfo = NULL;
	for (Shrek2Entity* ent : entities)
	{
		if (ent->ClassInfo)
		{
			classInfo = (Shrek2EntityClassInfo*)ent->ClassInfo;

			if (classInfo)
			{
				if (classInfo->ClassID == static_cast<int>(entityType)) {
					ents.push_back(ent);
				}
			}
		}
	}

	return ents;
}

std::vector<Shrek2Entity*> Shrek2EntityList::GetEntities(int classId)
{
	auto entities = FindEntities();
	if (entities.empty()) return {};

	std::vector<Shrek2Entity*> ents = {};

	Shrek2EntityClassInfo* classInfo = NULL;
	for (Shrek2Entity* ent : entities)
	{
		if (ent->ClassInfo)
		{
			classInfo = (Shrek2EntityClassInfo*)ent->ClassInfo;

			if (classInfo)
			{
				if (classInfo->ClassID == classId) {
					ents.push_back(ent);
				}
			}
		}
	}

	return ents;
}

Shrek2AnyCollection* Shrek2EntityList::GetCollection(Shrek2CollectionTypes collectionType)
{
	auto entities = FindEntities();
	if (entities.empty()) return NULL;

	Shrek2EntityClassInfo* classInfo = NULL;
	for (Shrek2Entity* ent : entities)
	{
		if (ent->ClassInfo)
		{
			classInfo = (Shrek2EntityClassInfo*)ent->ClassInfo;

			if (classInfo)
			{
				if (classInfo->ClassID == static_cast<int>(collectionType)) {
					return (Shrek2AnyCollection*)ent;
				}
			}
		}
	}

	return NULL;
}

std::vector<Shrek2Entity*> Shrek2EntityList::LoadEntities(uintptr_t ptr)
{
	int failCounter = 0;
	std::vector<Shrek2Entity*> entities;
	for (int i = 0; i < 9999; ++i)
	{
		uintptr_t pointer = *(uintptr_t*)(ptr + (i * 4));
		if (pointer)
		{
			failCounter = 0;
			Shrek2Entity* entity = (Shrek2Entity*)pointer;
			entities.push_back(entity);
		}
		else {
			failCounter++;
		}
		if (failCounter > 5)
			return entities;
	}
	return entities;
}

std::vector<Shrek2Entity*> Shrek2EntityList::FindEntities()
{
	DWORD addr = Shrek2Memory::GetAddr("Engine.dll", 0x004E85F0, 0x18C, 0x334, 0x30, 0x88);
	if (addr)
	{
		auto entities = LoadEntities(addr);
		if (entities.size() > 0)
		{
			std::vector<Shrek2Entity*> validEntities;
			for (Shrek2Entity* ent : entities)
			{
				if (IsValidEntity(ent)) {
					validEntities.push_back(ent);
				}
			}
			return validEntities;
		}
	}
	return {};
}

bool Shrek2EntityList::TestEntityValidity(Shrek2Entity* ent)
{
	MEMORY_BASIC_INFORMATION mbi0;
	VirtualQuery(ent, &mbi0, sizeof(mbi0));

	if (mbi0.Protect & PAGE_READWRITE)
	{
		Shrek2EntityClassInfo* classInfo = NULL;
		if (ent->ClassInfo)
		{
			classInfo = (Shrek2EntityClassInfo*)ent->ClassInfo;

			if (classInfo)
			{
				return true;
			}
		}
	}
	return false;
}

bool Shrek2EntityList::IsValidEntity(Shrek2Entity* ent)
{
	__try {
		return TestEntityValidity(ent);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

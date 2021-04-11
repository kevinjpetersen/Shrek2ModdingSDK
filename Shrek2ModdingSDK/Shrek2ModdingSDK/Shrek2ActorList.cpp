#include "Shrek2ModdingSDK.h"

bool Shrek2ActorList::Exists(Shrek2ActorTypes actorType)
{
	auto actors = FindActors();
	if (actors.empty()) return false;

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo->ClassID == static_cast<int>(actorType)) {
			return true;
		}
	}
	return false;
}

bool Shrek2ActorList::Exists(int classId)
{
	auto actors = FindActors();
	if (actors.empty()) return false;

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo->ClassID == classId) {
			return true;
		}
	}
	return false;
}

Shrek2Actor* Shrek2ActorList::GetActor(Shrek2ActorTypes actorType)
{
	auto actors = FindActors();
	if (actors.empty()) return NULL;

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo->ClassID == static_cast<int>(actorType)) {
			return actor;
		}
	}

	return NULL;
}

Shrek2Actor* Shrek2ActorList::GetActor(int classId)
{
	auto actors = FindActors();
	if (actors.empty()) return NULL;

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo->ClassID == classId) {
			return actor;
		}
	}

	return NULL;
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(Shrek2ActorTypes actorType)
{
	auto actors = FindActors();
	if (actors.empty()) return {};

	std::vector<Shrek2Actor*> foundActors = {};

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo)
		{
			if (actor->ClassInfo->ClassID == static_cast<int>(actorType)) {
				foundActors.push_back(actor);
			}
		}
	}

	return foundActors;
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(int classId)
{
	auto actors = FindActors();
	if (actors.empty()) return {};

	std::vector<Shrek2Actor*> foundActors = {};

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo)
		{
			if (actor->ClassInfo->ClassID == classId) {
				foundActors.push_back(actor);
			}
		}
	}

	return foundActors;
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors()
{
	auto actors = FindActors();
	if (actors.empty()) return {};
	return actors;
}

Shrek2AnyCollection* Shrek2ActorList::GetCollection(Shrek2CollectionTypes collectionType)
{
	auto actors = FindActors();
	if (actors.empty()) return NULL;

	for (Shrek2Actor* actor : actors)
	{
		if (actor->ClassInfo->ClassID == static_cast<int>(collectionType)) {
			return (Shrek2AnyCollection*)actor;
		}
	}

	return NULL;
}

std::vector<Shrek2Actor*> Shrek2ActorList::LoadActors(uintptr_t ptr)
{
	int failCounter = 0;
	std::vector<Shrek2Actor*> actors;
	for (int i = 0; i < 9999; ++i)
	{
		uintptr_t pointer = *(uintptr_t*)(ptr + (i * 4));
		if (pointer)
		{
			failCounter = 0;
			Shrek2Actor* actor = (Shrek2Actor*)pointer;
			actors.push_back(actor);
		}
		else {
			failCounter++;
		}
		if (failCounter > 5)
			return actors;
	}
	return actors;
}

std::vector<Shrek2Actor*> Shrek2ActorList::FindActors()
{
	DWORD addr = Shrek2Memory::GetAddr("Engine.dll", 0x004E85F0, 0x18C, 0x334, 0x30, 0x88);
	if (addr)
	{
		auto actors = LoadActors(addr);
		if (actors.size() > 0)
		{
			std::vector<Shrek2Actor*> validActors;
			for (Shrek2Actor* actor : actors)
			{
				if (IsValidActor(actor)) {
					validActors.push_back(actor);
				}
			}
			return validActors;
		}
	}
	return {};
}

bool Shrek2ActorList::TestActorValidity(Shrek2Actor* actor)
{
	MEMORY_BASIC_INFORMATION mbi0;
	VirtualQuery(actor, &mbi0, sizeof(mbi0));

	if (mbi0.Protect & PAGE_READWRITE)
	{
		if (actor->ClassInfo)
		{
			return true;
		}
	}
	return false;
}

bool Shrek2ActorList::IsValidActor(Shrek2Actor* actor)
{
	__try {
		return TestActorValidity(actor);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

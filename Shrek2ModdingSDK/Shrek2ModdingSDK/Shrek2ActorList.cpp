#include "Shrek2ModdingSDK.h"

bool Shrek2ActorList::Exists(Shrek2ActorTypes actorType)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::Exists2", ex.what());
		return false;
	}
}

bool Shrek2ActorList::Exists(int classId)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::Exists1", ex.what());
		return false;
	}
}

Shrek2Actor* Shrek2ActorList::GetActor(Shrek2ActorTypes actorType)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActor2", ex.what());
		return NULL;
	}
}

Shrek2Actor* Shrek2ActorList::GetActor(int classId)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActor1", ex.what());
		return NULL;
	}
}

Shrek2Actor* Shrek2ActorList::GetActor(int classId, std::string label)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (actor->ClassInfo->ClassID == classId && Shrek2Utils::DoesEqual(actor->GetLabel(), label)) {
				return actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActor3", ex.what());
		return NULL;
	}
}

Shrek2Actor* Shrek2ActorList::GetActor(std::string label)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (Shrek2Utils::DoesEqual(actor->GetLabel(), label)) {
				return actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActor4", ex.what());
		return NULL;
	}
}

Shrek2Actor* Shrek2ActorList::GetActor(Shrek2ActorTypes actorType, std::string label)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (actor->ClassInfo->ClassID == static_cast<int>(actorType) && Shrek2Utils::DoesEqual(actor->GetLabel(), label)) {
				return actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActor4", ex.what());
		return NULL;
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(std::vector<Shrek2ActorTypes> actorTypes)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return {};

		std::vector<Shrek2Actor*> foundActors = {};

		for (Shrek2Actor* actor : actors)
		{
			for (Shrek2ActorTypes actorType : actorTypes)
			{
				if (actor->ClassInfo)
				{
					if (actor->ClassInfo->ClassID == static_cast<int>(actorType)) {
						foundActors.push_back(actor);
					}
				}
			}
		}

		return foundActors;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActors4", ex.what());
		return {};
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(std::vector<int> classIds)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return {};

		std::vector<Shrek2Actor*> foundActors = {};

		for (Shrek2Actor* actor : actors)
		{
			for (int classId : classIds)
			{
				if (actor->ClassInfo)
				{
					if (actor->ClassInfo->ClassID == classId) {
						foundActors.push_back(actor);
					}
				}
			}
		}

		return foundActors;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActors5", ex.what());
		return {};
	}
}

Shrek2ActorCharacter* Shrek2ActorList::GetCharacter(Shrek2CharacterTypes characterType)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (actor->ClassInfo->ClassID == static_cast<int>(characterType)) {
				return (Shrek2ActorCharacter*)actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetCharacter", ex.what());
		return NULL;
	}
}

Shrek2ActorCharacter* Shrek2ActorList::GetCharacter(Shrek2CharacterTypes characterType, std::string label)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (actor->ClassInfo->ClassID == static_cast<int>(characterType) && Shrek2Utils::DoesEqual(actor->GetLabel(), label)) {
				return (Shrek2ActorCharacter*)actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetCharacter2", ex.what());
		return NULL;
	}
}

Shrek2ActorCharacter* Shrek2ActorList::GetCharacter(std::string label)
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return NULL;

		for (Shrek2Actor* actor : actors)
		{
			if (Shrek2Utils::DoesEqual(actor->GetLabel(), label)) {
				return (Shrek2ActorCharacter*)actor;
			}
		}

		return NULL;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetCharacter3", ex.what());
		return NULL;
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(Shrek2ActorTypes actorType)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActors3", ex.what());
		return {};
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors(int classId)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActors2", ex.what());
		return {};
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::GetActors()
{
	try {
		auto actors = FindActors();
		if (actors.empty()) return {};
		return actors;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetActors1", ex.what());
		return {};
	}
}

Shrek2AnyCollection* Shrek2ActorList::GetCollection(Shrek2CollectionTypes collectionType)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::GetCollection", ex.what());
		return NULL;
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::LoadActors(uintptr_t ptr)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::LoadActors", ex.what());
		return {};
	}
}

std::vector<Shrek2Actor*> Shrek2ActorList::FindActors()
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::FindActors", ex.what());
		return {};
	}
}

bool Shrek2ActorList::TestActorValidity(Shrek2Actor* actor)
{
	try {
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
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2ActorList::TestActorValidity", ex.what());
		return false;
	}
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

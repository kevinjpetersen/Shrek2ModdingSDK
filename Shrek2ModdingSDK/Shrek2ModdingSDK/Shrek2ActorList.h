#pragma once
class Shrek2ActorList
{
public:
	static bool Exists(Shrek2ActorTypes actorType);
	static bool Exists(int classId);

	static Shrek2Actor* GetActor(Shrek2ActorTypes actorType);
	static Shrek2Actor* GetActor(int classId);

	static std::vector<Shrek2Actor*> GetActors(Shrek2ActorTypes actorType);
	static std::vector<Shrek2Actor*> GetActors(int classId);
	static std::vector<Shrek2Actor*> GetActors();

	static Shrek2AnyCollection* GetCollection(Shrek2CollectionTypes collectionType);
private:
	static std::vector<Shrek2Actor*> LoadActors(uintptr_t ptr);
	static std::vector<Shrek2Actor*> FindActors();
	static bool TestActorValidity(Shrek2Actor* actor);
	static bool IsValidActor(Shrek2Actor* actor);
};


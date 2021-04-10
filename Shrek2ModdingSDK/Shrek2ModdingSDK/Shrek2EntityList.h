#pragma once
class Shrek2EntityList
{
public:
	static std::vector<Shrek2Entity*> GetEntities(Shrek2EntityTypes entityType);
	static std::vector<Shrek2Entity*> GetEntities(int classId);
	static Shrek2AnyCollection* GetCollection(Shrek2CollectionTypes collectionType);
private:
	static std::vector<Shrek2Entity*> LoadEntities(uintptr_t ptr);
	static std::vector<Shrek2Entity*> FindEntities();
	static bool TestEntityValidity(Shrek2Entity* ent);
	static bool IsValidEntity(Shrek2Entity* ent);
};


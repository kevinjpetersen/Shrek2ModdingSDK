#pragma once
class Shrek2EntityList
{
public:
	std::vector<Shrek2Entity*> GetEntities(Shrek2EntityTypes entityType);
	std::vector<Shrek2Entity*> GetEntities(int classId);
	Shrek2AnyCollection* GetCollection(Shrek2CollectionTypes collectionType);
private:
	std::vector<Shrek2Entity*> LoadEntities(uintptr_t ptr);
	std::vector<Shrek2Entity*> FindEntities();
	bool TestEntityValidity(Shrek2Entity* ent);
	bool IsValidEntity(Shrek2Entity* ent);
};


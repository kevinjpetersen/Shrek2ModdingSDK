#include "Shrek2ModdingSDK.h"

bool Shrek2Storage::Load()
{
	try
	{
		std::string filePath = DllPath + "\\" + "saved_variables.json";
		if (SavedVariablesExists(filePath) == false) {
			IsLoaded = false;
			return false;
		}

		std::ifstream t(filePath);
		std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		LoadedJson = json::parse(str);
		IsLoaded = true;

		return true;
	}
	catch (std::exception ex)
	{
		IsLoaded = false;
		return false;
	}
}

bool Shrek2Storage::Save()
{
	try
	{
		std::string filePath = DllPath + "\\" + "saved_variables.json";

		std::ofstream ofs(filePath, std::ofstream::trunc);
		ofs << LoadedJson.dump(4);
		ofs.close();

		return true;
	}
	catch (std::exception ex)
	{
		return false;
	}
}

std::string Shrek2Storage::GetString(std::string fieldName)
{
	if (!Load()) return "";
	if (LoadedJson.count(fieldName) == 0) return "";
	return (std::string)LoadedJson[fieldName];
}

int Shrek2Storage::GetInt(std::string fieldName)
{
	if (!Load()) return 0;
	if (LoadedJson.count(fieldName) == 0) return 0;
	return (int)LoadedJson[fieldName];
}

bool Shrek2Storage::GetBool(std::string fieldName)
{
	if (!Load()) return false;
	if (LoadedJson.count(fieldName) == 0) return false;
	return (bool)LoadedJson[fieldName];
}

float Shrek2Storage::GetFloat(std::string fieldName)
{
	if (!Load()) return 0;
	if (LoadedJson.count(fieldName) == 0) return 0;
	return (float)LoadedJson[fieldName];
}

long Shrek2Storage::GetLong(std::string fieldName)
{
	if (!Load()) return 0;
	if (LoadedJson.count(fieldName) == 0) return 0;
	return (long)LoadedJson[fieldName];
}

bool Shrek2Storage::SetString(std::string fieldName, std::string fieldValue)
{
	LoadedJson[fieldName] = fieldValue;
	return Save();
}

bool Shrek2Storage::SetInt(std::string fieldName, int fieldValue)
{
	LoadedJson[fieldName] = fieldValue;
	return Save();
}

bool Shrek2Storage::SetBool(std::string fieldName, bool fieldValue)
{
	LoadedJson[fieldName] = fieldValue;
	return Save();
}

bool Shrek2Storage::SetFloat(std::string fieldName, float fieldValue)
{
	LoadedJson[fieldName] = fieldValue;
	return Save();
}

bool Shrek2Storage::SetLong(std::string fieldName, long fieldValue)
{
	LoadedJson[fieldName] = fieldValue;
	return Save();
}

bool Shrek2Storage::SavedVariablesExists(std::string name)
{
	std::ifstream f(name.c_str());
	return f.good();
}

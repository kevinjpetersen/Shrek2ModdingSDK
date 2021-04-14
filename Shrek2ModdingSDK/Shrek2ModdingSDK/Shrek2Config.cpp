#include "Shrek2ModdingSDK.h"

bool Shrek2Config::Load()
{
	try 
	{
		std::string configPath = DllPath + "\\" + "config.json";
		if (ConfigExists(configPath) == false) {
			IsLoaded = false;
			return false;
		}

		std::ifstream t(configPath);
		std::string str((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		LoadedJson = json::parse(str);
		IsLoaded = true;

		return true;
	}
	catch (std::exception& ex)
	{
		IsLoaded = false;
		Shrek2Logging::LogError("Shrek2Config::Load", ex.what());
		return false;
	}
}

std::string Shrek2Config::GetString(std::string fieldName)
{
	if (!IsLoaded) return "";
	return LoadedJson["Config"][fieldName];
}

int Shrek2Config::GetInt(std::string fieldName)
{
	if (!IsLoaded) return 0;
	return LoadedJson["Config"][fieldName];
}

bool Shrek2Config::GetBool(std::string fieldName)
{
	if (!IsLoaded) return false;
	return LoadedJson["Config"][fieldName];
}

float Shrek2Config::GetFloat(std::string fieldName)
{
	if (!IsLoaded) return 0;
	return LoadedJson["Config"][fieldName];
}

long Shrek2Config::GetLong(std::string fieldName)
{
	if (!IsLoaded) return 0;
	return LoadedJson["Config"][fieldName];
}

bool Shrek2Config::ConfigExists(std::string name)
{
	std::ifstream f(name.c_str());
	return f.good();
}

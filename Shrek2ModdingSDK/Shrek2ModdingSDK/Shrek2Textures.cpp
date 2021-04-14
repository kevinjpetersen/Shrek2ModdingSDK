/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2DirectX.h"
#define D3D_RELEASE(D3D_PTR) if( D3D_PTR ){ D3D_PTR->Release(); D3D_PTR = NULL; }

bool Shrek2Textures::AddTexture(std::string path, std::string alias)
{
	try {
		if (AliasExist(alias)) return false;
		std::string formattedPath = Shrek2StaticVars::DllFolderPath + "\\" + path;

		AddedTextures.insert(std::pair<std::string, Shrek2Texture>(alias, Shrek2Texture(formattedPath.c_str())));
		return true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::AddTexture", ex.what());
		return false;
	}
}

bool Shrek2Textures::RemoveTexture(std::string alias)
{
	try {
		if (AliasExist(alias) == false) return false;
	
		AddedTextures.erase(alias);
		return true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::RemoveTexture", ex.what());
		return false;
	}
}

Shrek2Texture Shrek2Textures::GetTexture(std::string alias)
{
	try {
		auto item = AddedTextures[alias];
		return item;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::GetTexture", ex.what());
		return Shrek2Texture();
	}
}

bool Shrek2Textures::AliasExist(std::string alias)
{
	try {
		return AddedTextures.count(alias) > 0;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::AliasExist", ex.what());
		return false;
	}
}

void Shrek2Textures::InitializeTextures(IDirect3DDevice8* pDevice)
{
	try {
		if (!InitializedTextures) {
			InitializedTextures = true;
			if (AddedTextures.size() > 0)
			{
				std::list<std::string> keys;
				for (auto texture : AddedTextures)
				{
					keys.push_back(texture.first);
				}

				for (auto key : keys)
				{
					AddedTextures[key].SetIDirect3DTexture(pDevice);
				}
			}
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::InitializeTextures", ex.what());
	}
}

void Shrek2Textures::ReleaseTextures()
{
	try {
		if (InitializedTextures)
		{
			if (AddedTextures.size() > 0)
			{
				for (auto texture : AddedTextures)
				{
					auto& t = texture.second;
					D3D_RELEASE(t.Texture);
				}
			}
			InitializedTextures = false;
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Textures::ReleaseTextures", ex.what());
	}
}

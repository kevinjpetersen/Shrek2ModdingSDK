#include "Shrek2DirectX.h"
#define D3D_RELEASE(D3D_PTR) if( D3D_PTR ){ D3D_PTR->Release(); D3D_PTR = NULL; }

bool Shrek2Textures::AddTexture(std::string path, std::string alias)
{
	if (AliasExist(alias)) return false;
	std::string formattedPath = Shrek2StaticVars::DllFolderPath + "\\" + path;

	AddedTextures.insert(std::pair<std::string, Shrek2Texture>(alias, Shrek2Texture(formattedPath.c_str())));
	return true;
}

bool Shrek2Textures::RemoveTexture(std::string alias)
{
	if (AliasExist(alias) == false) return false;
	
	AddedTextures.erase(alias);
	return true;
}

Shrek2Texture Shrek2Textures::GetTexture(std::string alias)
{
	auto item = AddedTextures[alias];
	return item;
}

bool Shrek2Textures::AliasExist(std::string alias)
{
	return AddedTextures.count(alias) > 0;
}

void Shrek2Textures::InitializeTextures(IDirect3DDevice8* pDevice)
{
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

void Shrek2Textures::ReleaseTextures()
{
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
	}
}

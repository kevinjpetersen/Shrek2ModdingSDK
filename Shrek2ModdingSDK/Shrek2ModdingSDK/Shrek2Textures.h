#pragma once
class Shrek2Textures
{
public:
	Shrek2Texture sh2o_logo = Shrek2Texture("Shrek 2 Mods/Shrek 2 Test Mod/Images/gameicon.png");
	Shrek2Texture sh2o_logo2 = Shrek2Texture("Shrek 2 Mods/Shrek 2 Test Mod/Images/master64.jpg");

	Shrek2Textures() {

	}

	bool AddTexture(std::string path, std::string alias);
	bool RemoveTexture(std::string alias);
	Shrek2Texture GetTexture(std::string alias);

	void InitializeTextures(IDirect3DDevice8* pDevice);
	void ReleaseTextures();
};


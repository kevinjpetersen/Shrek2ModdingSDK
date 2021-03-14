#pragma once
class Shrek2Textures
{
public:
	Shrek2Texture sh2o_logo = Shrek2Texture("gameicon.png");

	Shrek2Textures() {

	}

	void InitializeTextures(IDirect3DDevice8* pDevice);
	void ReleaseTextures();
};


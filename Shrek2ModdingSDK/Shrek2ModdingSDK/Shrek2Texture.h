#pragma once
class Shrek2Texture
{
public:
	LPCSTR TextureFileLocation;
	IDirect3DTexture8* Texture;

	Shrek2Texture(LPCSTR textureFileLocation) {
		TextureFileLocation = textureFileLocation;
	}

	void SetIDirect3DTexture(IDirect3DDevice8* pDevice);
};


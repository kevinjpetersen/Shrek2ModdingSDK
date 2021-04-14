/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2DirectX.h"

void Shrek2Texture::SetIDirect3DTexture(IDirect3DDevice8* pDevice)
{
	try {
		D3DXCreateTextureFromFile(pDevice, TextureFileLocation.c_str(), &Texture);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2Texture::SetIDirect3DTexture", ex.what());
	}
}

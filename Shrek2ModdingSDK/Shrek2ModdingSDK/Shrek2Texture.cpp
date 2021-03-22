/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2DirectX.h"

void Shrek2Texture::SetIDirect3DTexture(IDirect3DDevice8* pDevice)
{
	D3DXCreateTextureFromFile(pDevice, TextureFileLocation.c_str(), &Texture);
}

#include "Shrek2DirectX.h"

void Shrek2Texture::SetIDirect3DTexture(IDirect3DDevice8* pDevice)
{
	D3DXCreateTextureFromFile(pDevice, TextureFileLocation, &Texture);
}

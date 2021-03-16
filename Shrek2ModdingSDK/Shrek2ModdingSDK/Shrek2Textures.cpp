#include "Shrek2DirectX.h"
#define D3D_RELEASE(D3D_PTR) if( D3D_PTR ){ D3D_PTR->Release(); D3D_PTR = NULL; }

void Shrek2Textures::InitializeTextures(IDirect3DDevice8* pDevice)
{
	if (!sh2o_logo.Texture) sh2o_logo.SetIDirect3DTexture(pDevice);
	if (!sh2o_logo2.Texture) sh2o_logo2.SetIDirect3DTexture(pDevice);
}

void Shrek2Textures::ReleaseTextures()
{
	D3D_RELEASE(sh2o_logo.Texture);
	D3D_RELEASE(sh2o_logo2.Texture);
}

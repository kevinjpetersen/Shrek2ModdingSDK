#include "Shrek2UI.h"

void Shrek2UI::Initialize()
{
	std::cout << "Trying to attach to Shrek 2's UI Pipeline (DirectX)" << std::endl;
	bool hasHookedEndScene = false;
	while (hasHookedEndScene == false) {
		hasHookedEndScene = HookEndScene();
		if (hasHookedEndScene == false) {
			Sleep(500);
		}
	}
	std::cout << "Successfully attached to Shrek 2's UI Pipeline (DirectX)" << std::endl;
}

void Shrek2UI::RenderText(std::string text, int x, int y)
{

}

HRESULT __stdcall Shrek2UI::hookedEndScene(IDirect3DDevice8* pDevice)
{
	GlobalPDevice = pDevice;
	RenderUI();
	return pEndScene(pDevice);
}

bool Shrek2UI::HookEndScene()
{
	IDirect3D8* pD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if (!pD3D) return false;

	D3DPRESENT_PARAMETERS d3dparams = { 0 };
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = GetForegroundWindow();
	d3dparams.Windowed = true;
	d3dparams.BackBufferHeight = 0L;
	d3dparams.BackBufferWidth = 0L;
	d3dparams.BackBufferFormat = D3DFMT_A8R8G8B8;

	IDirect3DDevice8* pDevice = NULL;

	HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dparams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
	if (FAILED(result) || !pDevice) {
		pD3D->Release();
		return false;
	}
	void** vTable = *reinterpret_cast<void***>(pDevice);

	pEndScene = (endScene)DetourFunction((PBYTE)vTable[35], (PBYTE)hookedEndScene);

	pDevice->Release();
	pD3D->Release();

	return true;
}
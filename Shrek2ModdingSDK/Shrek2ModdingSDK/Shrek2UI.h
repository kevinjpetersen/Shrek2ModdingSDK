#include <windows.h>
#include <iostream>
#include <d3d8.h>
#include <d3dx8.h>
#include <d3dx8core.h>
#include "detours.h"

#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "detours.lib")

namespace Shrek2UI
{
	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice8* pDevice);
	inline HRESULT __stdcall hookedEndScene(IDirect3DDevice8* pDevice);
	inline endScene pEndScene;
	void RenderEvent(IDirect3DDevice8* pDevice);
	bool HookEndScene();
	inline bool HasHookedEndScene;
	inline IDirect3DDevice8* GlobalPDevice;
	void Initialize();
	void RenderText(std::string text, int x, int y);
	inline void (*RenderUI)();
}
namespace Shrek2UI
{
	void Reset(IDirect3DDevice8* pDevice);

	void InitializeFonts(IDirect3DDevice8* pDevice);
	void InitializeSprite(IDirect3DDevice8* pDevice);

	void RenderRectangle(Shrek2Rect rect, D3DCOLOR color);
	void RenderText(Shrek2Rect rect, LPCSTR text, D3DCOLOR color, bool isNormalText);
	void RenderTexture(Shrek2Texture texture, Shrek2Position position, float rotation = 0, D3DXCOLOR color = 0xFFFFFFFF);

	void StopUI();
	inline bool IsUIRunning = false;

	D3DCOLOR GetColor(int r, int g, int b);

	inline LPD3DXFONT shNormalFont = NULL;
	inline HFONT hNormalFont;

	inline LPD3DXFONT shSmallFont = NULL;
	inline HFONT hSmallFont;

	inline ID3DXSprite* g_pSprite;

	inline bool ViewportLoaded = false;
	inline D3DVIEWPORT8 Viewport;
	inline RECT GameWindowSize;
	inline RECT LastGameWindowSize;

	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice8* pDevice);
	inline HRESULT __stdcall hookedEndScene(IDirect3DDevice8* pDevice);
	inline endScene pEndScene;
	bool HookEndScene();
	inline bool HasHookedEndScene;
	inline IDirect3DDevice8* GlobalPDevice;
	void Initialize();
	inline void (*RenderUI)();
}
#pragma once

struct GRAPHICS_DESC
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	float Width;
	float Height;
	bool bVsync;
	bool bWindowed;
	Color Background;
};

class Graphics : public Singleton<Graphics>
{
public:
	friend Singleton<Graphics>;

	static float Width() { return desc.Width; }
	static float Height() { return desc.Height; }

	static ID3D11Device* GetDevice() { return device; }
	static ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }
	static IDXGISwapChain* GetSwapChain() { return swapChain; }
	static const GRAPHICS_DESC& GetDesc() { return desc; }
	static void SetDesc(GRAPHICS_DESC& inDesc) { desc = inDesc; }

	void SetRenderTarget(ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL);

	void Clear(Color color = DEFAULT_COLOR, ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL);
	void Present();

	void ResizeScreen(float width, float height);

private:
	Graphics();
	~Graphics();

	void SetGPUInfo();
	void CreateSwapChainAndDevice();

	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

private:
	static GRAPHICS_DESC desc;
	static ID3D11Device* device;
	static ID3D11DeviceContext* deviceContext;
	static IDXGISwapChain* swapChain;

	ID3D11Debug* debugDevice;

	uint gpuMemorySize;
	wstring gpuDescription;

	uint numerator;
	uint denominator;

	ID3D11Texture2D* backBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RenderTargetView* renderTargetView;
};
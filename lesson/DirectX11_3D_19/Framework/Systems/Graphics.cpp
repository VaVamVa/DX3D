#include "Framework.h"
#include "Graphics.h"

GRAPHICS_DESC		 Graphics::desc;
ID3D11Device*		 Graphics::device = NULL;
ID3D11DeviceContext* Graphics::deviceContext = NULL;
IDXGISwapChain*		 Graphics::swapChain = NULL;

Graphics::Graphics()
	: numerator(0), denominator(0)
{
	SetGPUInfo();

	CreateSwapChainAndDevice();
	CreateBackBuffer(desc.Width, desc.Height);
}

Graphics::~Graphics()
{
	DeleteBackBuffer();

	if (swapChain)
		swapChain->SetFullscreenState(false, NULL);

	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
}

#pragma region public

void Graphics::SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == NULL)
		rtv = renderTargetView;

	if (dsv == NULL)
		dsv = depthStencilView;

	deviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void Graphics::Clear(Color color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
	if (rtv == NULL)
		rtv = renderTargetView;

	if (dsv == NULL)
		dsv = depthStencilView;

	deviceContext->ClearRenderTargetView(rtv, color);
	deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1, 0);
}

void Graphics::Present()
{
	swapChain->Present(desc.bVsync == true ? 1 : 0, 0);
}

void Graphics::ResizeScreen(float width, float height)
{
	if (width < 1 || height < 1) return;

	desc.Width = width;
	desc.Height = height;

	DeleteBackBuffer();
	{
		HRESULT hr = swapChain->ResizeBuffers(0, (uint)width, (uint)height, DXGI_FORMAT_UNKNOWN, 0);
		Check(hr);
	}
	CreateBackBuffer(width, height);
}

#pragma endregion

#pragma region private
void Graphics::SetGPUInfo()
{
	HRESULT hr;
	
	IDXGIFactory* factory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	Check(hr);

	IDXGIAdapter* adapter;
	hr = factory->EnumAdapters(0, &adapter);
	Check(hr);
	
	IDXGIOutput* output;
	hr = adapter->EnumOutputs(0, &output);
	Check(hr);

	uint modeCount;
	hr = output->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		NULL
	);
	Check(hr);

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	hr = output->GetDisplayModeList
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		displayModeList
	);
	Check(hr);

	for (uint i = 0; i < modeCount; i++)
	{
		bool bCheck = true;
		bCheck &= displayModeList[i].Width == desc.Width;
		bCheck &= displayModeList[i].Height == desc.Height;

		if (bCheck)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}
	
	DXGI_ADAPTER_DESC adapterDesc;
	hr = adapter->GetDesc(&adapterDesc);
	Check(hr);

	uint megaByte = 1024 * 1024;
	gpuMemorySize = adapterDesc.DedicatedVideoMemory / megaByte;
	gpuDescription = adapterDesc.Description;

	SAFE_DELETE_ARRAY(displayModeList);

	SAFE_RELEASE(output);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);
}

void Graphics::CreateSwapChainAndDevice()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(swapChain);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMem(swapChainDesc);

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (this->desc.bVsync == true)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = handle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = desc.bWindowed;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	uint creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);
	Check(hr);
}

void Graphics::CreateBackBuffer(float width, float height)
{
	HRESULT hr;

	// Get Back Buffer
	ID3D11Texture2D* pbackBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pbackBuffer);
	Check(hr);

	// Create RTV
	hr = device->CreateRenderTargetView(pbackBuffer, NULL, &renderTargetView);
	Check(hr);

	SAFE_RELEASE(pbackBuffer);

	// Create Depth Stencil Texture
	D3D11_TEXTURE2D_DESC dstDesc = { 0 };
	dstDesc.Width = (UINT)width;
	dstDesc.Height = (UINT)height;
	dstDesc.MipLevels = 1;
	dstDesc.ArraySize = 1;
	dstDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dstDesc.SampleDesc.Count = 1;
	dstDesc.SampleDesc.Quality = 0;
	dstDesc.Usage = D3D11_USAGE_DEFAULT;
	dstDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dstDesc.CPUAccessFlags = 0;
	dstDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&dstDesc, NULL, &backBuffer);
	Check(hr);

	// Create DSV
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMem(dsvDesc);
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = device->CreateDepthStencilView(backBuffer, &dsvDesc, &depthStencilView);
	Check(hr);

	SetRenderTarget(renderTargetView, depthStencilView);
}

void Graphics::DeleteBackBuffer()
{
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(backBuffer);
}
#pragma endregion
#include "jhGraphicDeviceDX11.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhMesh.h"
#include "jhConstantBuffer.h"

namespace jh::graphics
{
	// Device, DeviceContext, SwapChain ����.
	// RenderTaget, View, DepthStencil, View ����
	// OMSetRenderTargets(), RSSetViewports() ����.
	GraphicDevice_DX11::GraphicDevice_DX11(graphics::eValidationMode mode)
	{
		// 1. Device�� Swapchain�� �����Ѵ�.
		// 2. ����ۿ� ������ �������� ����Ÿ�� �並 �����ؾ� �Ѵ�.
		// 3. ȭ���� Ŭ���� ���־�� �Ѵ�. �� ��Ʈ�� �������־�� �Ѵ�.
		// 4. �� �����Ӹ��� ������ ������ ����Ÿ�� �信 ������ ���־�� �Ѵ�.
		// 5. Swapchain�� �̿��Ͽ� ���� ����̽�(���÷���)�� ȭ���� �������־�� �Ѵ�.

		// HWND hwnd = Application::GetInstance().GetHwnd();

		//// Device, DeviceContext
		//UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		//D3D_FEATURE_LEVEL featureLevel = static_cast<D3D_FEATURE_LEVEL>(0);

		//HRESULT hr = D3D11CreateDevice(
		//	nullptr,
		//	D3D_DRIVER_TYPE_HARDWARE,
		//	nullptr,
		//	deviceFlag,
		//	nullptr,
		//	0,
		//	D3D11_SDK_VERSION,
		//	mcpDevice.GetAddressOf(),
		//	&featureLevel,
		//	mcpContext.GetAddressOf()
		//);

		//if (FAILED(hr))
		//{
		//	assert(false);
		//}

		//// Swapchain
		//DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		//swapChainDesc.OutputWindow = hwnd;
		//swapChainDesc.Windowed = true;
		//swapChainDesc.BufferCount = 1;

		//swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//swapChainDesc.BufferDesc.Width = Application::GetInstance().GetWidth();
		//swapChainDesc.BufferDesc.Height = Application::GetInstance().GetHeight();
		//swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		//swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		//swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		//swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		//swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//swapChainDesc.SampleDesc.Count = 1;
		//swapChainDesc.SampleDesc.Quality = 0;

		//if (!CreateSwapChain(&swapChainDesc))
		//{
		//	assert(false);
		//	return;
		//}

		//// Get Rendertaget for swapchain
		//hr = mcpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mcpRenderTarget.GetAddressOf());
		//if (FAILED(hr)) { assert(false); }
		//// CreateRendertarget View
		//hr = mcpDevice->CreateRenderTargetView(mcpRenderTarget.Get(), nullptr, mcpRenderTargetView.GetAddressOf());
		//if (FAILED(hr)) { assert(false); }

		//D3D11_TEXTURE2D_DESC depthBufferDesc = {};
		//depthBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		//depthBufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		//depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//depthBufferDesc.CPUAccessFlags = 0;
		//depthBufferDesc.Width = Application::GetInstance().GetWidth();
		//depthBufferDesc.Height = Application::GetInstance().GetHeight();
		//depthBufferDesc.ArraySize = 1;
		//depthBufferDesc.SampleDesc.Count = 1;
		//depthBufferDesc.SampleDesc.Quality = 0;
		//depthBufferDesc.MipLevels = 1;
		//depthBufferDesc.MiscFlags = 0;

		//if (!CreateTexture(&depthBufferDesc, mcpDepthStencilBuffer.GetAddressOf()))
		//{
		//	assert(false);
		//	return;
		//}

		//CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		//if (FAILED(mcpDevice->CreateDepthStencilView(mcpDepthStencilBuffer.Get(), &depthStencilViewDesc, mcpDepthStencilView.ReleaseAndGetAddressOf())))
		//{
		//	assert(false);
		//	return;
		//}

		//mcpContext->OMSetRenderTargets(
		//	1,
		//	mcpRenderTargetView.GetAddressOf(),
		//	mcpDepthStencilView.Get()
		//);

		//RECT winRect;
		//GetClientRect(Application::GetInstance().GetHwnd(), &winRect);
		//mViewport = { 
		//	0.0f, 
		//	0.0f, 
		//	static_cast<FLOAT>(winRect.right - winRect.left), 
		//	static_cast<FLOAT>(winRect.bottom - winRect.top),
		//};

		//BindViewports(&mViewport);

		/*
			Direct3D �ʱ�ȭ ������
			1. ����̽�, ����̽� ���ؽ�Ʈ ����
			2. ����ü�� ����
			3. �� ���۸� ����Ÿ������ ����(����Ÿ�� �� ����)
			4. �X��-���ٽ� ���� ����. (�X��-���� �� ����)
			5. ����Ʈ�� ����
			6. ȭ�鿡 �׸���
		*/


		// Device, DeviceContext, SwapChain ����.
		// RenderTaget, View, DepthStencil, View ����
		// OMSetRenderTargets(), RSSetViewports() ����.
		// DXGI_SWAP_CHAIN_DESC - ����ü���� ���¸� �����ϴ� ����ü

		CreateSwapChain();
		CreateRenderTargetAndDepthStencilBuffer();
		BindViewports();
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		renderer::Release();
		mcpSamplerState.Reset();
		mcpDepthStencilView.Reset();
		mcpRenderTargetView.Reset();
		mcpDepthStencilBuffer.Reset();
		mcpRenderTarget.Reset();
		mcpSwapChain.Reset();
		mcpContext.Reset();
		mcpDevice.Reset();
	}
	bool GraphicDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* pSwapChainDesc)
	{

		//Microsoft::WRL::ComPtr<IDXGIDevice>		cpDXGIDevice;
		//Microsoft::WRL::ComPtr<IDXGIAdapter>	cpDXGIAdapter;
		//Microsoft::WRL::ComPtr<IDXGIFactory>	cpDXGIFactory;

		//if (FAILED(mcpDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)cpDXGIDevice.GetAddressOf())))
		//{
		//	assert(false);
		//	return false;
		//}

		//if (FAILED(cpDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)cpDXGIAdapter.GetAddressOf())))
		//{
		//	assert(false);
		//	return false;
		//}

		//if (FAILED(cpDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)cpDXGIFactory.GetAddressOf())))
		//{
		//	assert(false);
		//	return false;
		//}

		//if (FAILED(cpDXGIFactory->CreateSwapChain(mcpDevice.Get(), pSwapChainDesc, mcpSwapChain.GetAddressOf())))
		//{
		//	assert(false);
		//	return false;
		//}


		return true;
	}
	bool GraphicDevice_DX11::CreateSwapChain()
	{
		HWND hwnd = Application::GetInstance().GetHwnd();

		DXGI_SWAP_CHAIN_DESC scDesc{};

		ZeroMemory(&scDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		// ������� ������ ����.
		scDesc.BufferCount = 1;

		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// ������� �뵵�� ���ٱ����� ������.
		// ���⼭�� ��¿� ����Ÿ��(�׷��� ��)�̶�� ����. ����ۿ� ���� �׸��� �׸��� ������ �����.
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		// ����� ������ �ڵ�. �ʼ���.
		scDesc.OutputWindow = hwnd;

		// ��Ƽ���ø� �Ű������� ������. ���ü��� �����ϴ� Count��, ǰ���� �ǹ��ϴ� Quality�� �Ǿ� ����.
		// MSAA�� ������ Count == 1, Quality == 0���� �����Ǿ�� ��.
		// ���� : ����Ÿ�ٰ� �X�����۴� ������ �����̾�߸� ��!


		scDesc.BufferDesc.Width = Application::GetInstance().GetWidth();
		scDesc.BufferDesc.Height = Application::GetInstance().GetHeight();
		scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		scDesc.SampleDesc.Count = 1;
		// â����� ���, ����ȭ�� ��ü�� ������۰� �Ǹ�, 
		// ��üȭ�� ����� ���, ������ ������۰� �������.
		scDesc.Windowed = TRUE;


		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			NULL,                           // Dirext3D���� ����� �׷���ī�� ����. NULL�� �⺻ �׷���ī�带 ����Ѵٴ� �ǹ�
			D3D_DRIVER_TYPE_HARDWARE,       // �ϵ���� �Ǵ� ����Ʈ���� �������� ����� �������� ����.
			NULL,                           // HMODULE, ����Ʈ ���� ������ �����⸦ ����. �ַ� DLL�� ������.
			NULL,                           // Flags, Direct3D�� ��� ������ �������� ���� �÷��� ����.
			NULL,                           // D3D_FEATURE_LEVEL, ��ɼ����� ����. Direct3D11�� ����� ��쿡�� �׳� 0�� �Ѱ��ָ� ��.
			NULL,                           // FeatureLevels ������ 0�� �ָ�, ���⵵ 0�� �Ѱܾ���. �׷��� Direct3D11 ��ɼ����� �����.(��Ȯ���� D3D_FEATURE_LEVEL_11_0)
			D3D11_SDK_VERSION,              // ����� DirectX SDK ������ ���
			&scDesc,
			mcpSwapChain.ReleaseAndGetAddressOf(),
			mcpDevice.ReleaseAndGetAddressOf(),
			NULL,                           // ��ɼ��� �迭�� ��ȯ��.
			mcpContext.ReleaseAndGetAddressOf()
		);
		ifFailed(hr);
		return false;
	}
	bool GraphicDevice_DX11::CreateRenderTargetAndDepthStencilBuffer()
	{
		HRESULT hr;
		// SwapChain <- back �׸� ���� <- RenderTarget�� BackBuffer�� ����
		hr = mcpSwapChain->GetBuffer(
			0,                                                      // BackBuffer  
			IID_PPV_ARGS(mcpRenderTarget.ReleaseAndGetAddressOf())  // RenderTarget�� BackBuffer��.
		);
		ifFailed(hr);

		// Resource -> ResourceView�� ����
		mcpDevice->CreateRenderTargetView(
			mcpRenderTarget.Get(),
			nullptr,                                                // RENDER_TARGET_VIEW_DESC, NULL�� �����ϸ� �Ӹ� ���� 0�� ��� ���ν��� ���� ������ �䰡 ������.
			mcpRenderTargetView.GetAddressOf()
		);
		ifFailed(hr);

		// Depth-Stencil Buffer �����
		// C�� ���̸� ��ġ Ŭ�����ΰ� ó�� �� �� ����.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,              // 4Byte�ϱ�, �տ� 3����Ʈ�� depthBuffer��, ������ �� ����Ʈ�� Stencil�� ��.
			Application::GetInstance().GetWidth(),
			Application::GetInstance().GetHeight(),
			1,
			1,                                          // 1�� �ָ� �Ѵܰ踸 ����ϱ� ������ �����. �⺻���� 2*2���� ��������.
			D3D11_BIND_DEPTH_STENCIL                    // �ؽ��ĸ� ��� �뵵�� ����?
		);

		mcpDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			mcpDepthStencilBuffer.ReleaseAndGetAddressOf()
		);
		ifFailed(hr);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		mcpDevice->CreateDepthStencilView(
			mcpDepthStencilBuffer.Get(),
			&depthStencilViewDesc,
			mcpDepthStencilView.ReleaseAndGetAddressOf()
		);
		ifFailed(hr);

		// ����Ÿ�ٰ� �X��-���ٽ� ���۸� ���ε���. 
		mcpContext->OMSetRenderTargets(
			1,
			mcpRenderTargetView.GetAddressOf(),
			mcpDepthStencilView.Get()
		);
		return false;
	}
	bool GraphicDevice_DX11::CreateTexture(D3D11_TEXTURE2D_DESC* pTextureDesc, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mcpDevice->CreateTexture2D(pTextureDesc, nullptr, ppTexture2D)))
		{
			assert(false);
			return false;
		}
		return true;
	}

	bool GraphicDevice_DX11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements, const void* pShaderByteInputSignature, SIZE_T byteCodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mcpDevice->CreateInputLayout(pDesc, numElements, pShaderByteInputSignature, byteCodeLength, ppInputLayout)))
		{
			assert(false);
			return false;
		}
		return true;
	}

	bool GraphicDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* pBufferDesc, D3D11_SUBRESOURCE_DATA* pSubResourceData, ID3D11Buffer** ppBuffer)
	{
		// System -> GPU
		if (FAILED(mcpDevice->CreateBuffer(pBufferDesc, pSubResourceData, ppBuffer)))
		{
			assert(false);
			return false;
		}
		return true;
	}

	bool GraphicDevice_DX11::CreateAndSetShader()
	{
		//// VertexShader 
		//std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		//shaderPath += "SHADER_SOURCE\\";

		//std::wstring vsPath(shaderPath.c_str());
		//vsPath += L"TriangleVS.hlsl";
		//HRESULT hr;

		//hr = D3DCompileFromFile(
		//	vsPath.c_str(),
		//	nullptr,
		//	D3D_COMPILE_STANDARD_FILE_INCLUDE,
		//	"VS_Test",
		//	"vs_5_0",
		//	0,
		//	0,
		//	renderer::cpVertexShaderBlob.ReleaseAndGetAddressOf(),
		//	renderer::cpErrorBlob.ReleaseAndGetAddressOf()
		//);
		//if (FAILED(hr))
		//{
		//	OutputDebugStringA((char*)renderer::cpErrorBlob->GetBufferPointer());
		//	renderer::cpErrorBlob->Release();
		//	renderer::cpErrorBlob = nullptr;
		//	assert(false);
		//}

		//hr = mcpDevice->CreateVertexShader(
		//	renderer::cpVertexShaderBlob->GetBufferPointer(),
		//	renderer::cpVertexShaderBlob->GetBufferSize(),
		//	nullptr,
		//	renderer::cpVertexShader.ReleaseAndGetAddressOf()
		//);
		//if (FAILED(hr)) assert(false);

		//std::wstring psPath(shaderPath.c_str());
		//psPath += L"TrianglePS.hlsl";

		//hr = D3DCompileFromFile(
		//	psPath.c_str(),
		//	nullptr,
		//	D3D_COMPILE_STANDARD_FILE_INCLUDE,
		//	"PS_Test",
		//	"ps_4_0",
		//	0,
		//	0,
		//	renderer::cpPixelShaderBlob.ReleaseAndGetAddressOf(),
		//	renderer::cpErrorBlob.ReleaseAndGetAddressOf()
		//);


		//if (FAILED(hr))
		//{
		//	OutputDebugStringA( (char*)renderer::cpErrorBlob->GetBufferPointer());
		//	renderer::cpErrorBlob->Release();
		//	renderer::cpErrorBlob = nullptr;
		//	assert(false);
		//}

		//hr = mcpDevice->CreatePixelShader(
		//	renderer::cpPixelShaderBlob->GetBufferPointer(),
		//	renderer::cpPixelShaderBlob->GetBufferSize(),
		//	nullptr,
		//	renderer::cpPixelShader.ReleaseAndGetAddressOf()
		//);
		//if (FAILED(hr)) assert(false);

		//mcpContext->VSSetShader(renderer::cpVertexShader.Get(), nullptr, 0);
		//mcpContext->PSSetShader(renderer::cpPixelShader.Get(), nullptr, 0);

		return true;
	}

	bool GraphicDevice_DX11::CreateVertexShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		HRESULT hr = mcpDevice->CreateVertexShader(
			pShaderByteCode,
			byteCodeLength,
			pClassLinkage,
			ppVertexShader
		);
		if (FAILED(hr)) assert(false);
		return true;
	}

	bool graphics::GraphicDevice_DX11::CreatePixelShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{
		HRESULT hr = mcpDevice->CreatePixelShader(
			pShaderByteCode,
			byteCodeLength,
			pClassLinkage,
			ppPixelShader
		);
		if (FAILED(hr)) assert(false);
		return true;
	}

	void GraphicDevice_DX11::BindViewports(D3D11_VIEWPORT* pViewport)
	{
		mcpContext->RSSetViewports(1, pViewport);
	}

	void GraphicDevice_DX11::BindViewports()
	{
		CD3D11_VIEWPORT viewPort(
			0.0f,
			0.0f,
			static_cast<float>(Application::GetInstance().GetWidth()),
			static_cast<float>(Application::GetInstance().GetHeight())
		);

		// ����Ʈ ���ε� (Rasterizer Stage -> RS)
		mcpContext->RSSetViewports(1, &viewPort);
	}

	void GraphicDevice_DX11::WriteConstantBufferAtGPU(ID3D11Buffer* pBuffer, void* pData, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;

		// �Ѱ��� �����͸� �����Ͽ� ���ε� ���� ���ҽ� ����ü�� ä����.
		// �����ϸ� �� ���ҽ��� GPU�� �бⰡ ���� ��.
		HRESULT hr;
		hr = mcpContext->Map(
			pBuffer,							// ������ ���ҽ�. 
			0,									// ���긮�ҽ��� �ε���. �츮�� ��°�� �Ѱ��ֹǷ� ������ �ʿ� ����
			D3D11_MAP_WRITE_DISCARD,			// ���ι���� ����. D3D11_MAP_WRITE_DISCARD �ǹ̴� ���� ���� ������ �ִ� ���� ������� �ǹ�.
			0,									// �߰� �ɼ����� GPU�� �ٺ��� ����ϰ� ���� ��, CPU�� �۾��� �����Ѵ�. ����� DO_NOT_WAIT�� ���ǵǾ� ����. �츮�� GPU�� ����� ������ ���� ��ٸ� �� ���ۿ� ���� ä���� �ϴϱ� NULL�� �ָ� ��.
			&mappedSubResource					// ���ε� ���ҽ��� ����ü�� ������. �߿��Ѱ��� ��� pData��. ���⿡ ���ҽ��� ���� �����������Ͱ� void*�� �������.
		);
		ifFailed(hr);

		// �� �������� ���� �����ϰ� ���� �����ص� �Ǹ� �����ϰ� ��.
		// ���ε� ���긮�ҽ��� pData�� ���ؽ� ����ü���� �޸� �����ϸ� ��.
		memcpy(mappedSubResource.pData, pData, size);
		mcpContext->Unmap(pBuffer, 0);

	}

	void GraphicDevice_DX11::SetConstantBufferAtShader(eShaderStage shaderStage, eConstantBufferType eType, ID3D11Buffer* pBuffer)
	{
		switch (shaderStage)
		{
		case jh::graphics::eShaderStage::VERTEX_SHADER:
			mcpContext->VSSetConstantBuffers(static_cast<UINT>(eType), 1, &pBuffer);
			break;
		case jh::graphics::eShaderStage::PIXEL_SHADER:
			mcpContext->PSSetConstantBuffers(static_cast<UINT>(eType), 1, &pBuffer);
			break;
		case jh::graphics::eShaderStage::COUNT:
			assert(false);
			break;
		default:
			break;
		}
	}

	void graphics::GraphicDevice_DX11::SetVertexBufferAtIA(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* pBuffer, const UINT* pStride, const UINT* pOffeset)
	{
		mcpContext->IASetVertexBuffers(
			startSlot,
			numBuffers,
			pBuffer,
			pStride,
			pOffeset
		);
	}

	void graphics::GraphicDevice_DX11::SetIndexBufferAtIA(ID3D11Buffer* pIdxBuffer, DXGI_FORMAT format, UINT offset)
	{
		mcpContext->IASetIndexBuffer(
			pIdxBuffer,
			format,
			offset
		);
	}

	void graphics::GraphicDevice_DX11::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mcpContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void graphics::GraphicDevice_DX11::SetInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mcpContext->IASetInputLayout(pInputLayout);
	}

	void graphics::GraphicDevice_DX11::SetVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances)
	{
		mcpContext->VSSetShader(pVertexShader, ppClassInstance, numClassInstances);
	}

	void graphics::GraphicDevice_DX11::SetPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances)
	{
		mcpContext->PSSetShader(pPixelShader, ppClassInstance, numClassInstances);
	}

	void GraphicDevice_DX11::Present()
	{
		mcpSwapChain->Present(0, 0);
	}

	void GraphicDevice_DX11::DrawIndexed(UINT idxCount, UINT startIdxLocation, UINT baseVertexLocation)
	{
		mcpContext->DrawIndexed(idxCount, startIdxLocation, baseVertexLocation);
	}
}

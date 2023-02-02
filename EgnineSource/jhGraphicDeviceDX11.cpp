#include "jhGraphicDeviceDX11.h"
#include "jhApplication.h"
#include "jhRenderer.h"
#include "jhMesh.h"
#include "jhConstantBuffer.h"

namespace jh::graphics
{
	// Device, DeviceContext, SwapChain 생성.
	// RenderTaget, View, DepthStencil, View 생성
	// OMSetRenderTargets(), RSSetViewports() 까지.
	GraphicDevice_DX11::GraphicDevice_DX11(graphics::eValidationMode mode)
	{
		// 1. Device와 Swapchain을 생성한다.
		// 2. 백버퍼에 실제로 렌더링할 렌더타겟 뷰를 생성해야 한다.
		// 3. 화면을 클리어 해주어야 한다. 뷰 포트를 생성해주어야 한다.
		// 4. 매 프레임마다 위에서 생성한 렌더타겟 뷰에 렌더링 해주어야 한다.
		// 5. Swapchain을 이용하여 최종 디바이스(디스플레이)에 화면을 렌더해주어야 한다.

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
			Direct3D 초기화 시퀀스
			1. 디바이스, 디바이스 컨텍스트 생성
			2. 스왑체인 생성
			3. 백 버퍼를 렌더타겟으로 지정(렌더타겟 뷰 생성)
			4. 뎊스-스텐실 버퍼 생성. (뎊스-버퍼 뷰 생성)
			5. 뷰포트를 지정
			6. 화면에 그리기
		*/


		// Device, DeviceContext, SwapChain 생성.
		// RenderTaget, View, DepthStencil, View 생성
		// OMSetRenderTargets(), RSSetViewports() 까지.
		// DXGI_SWAP_CHAIN_DESC - 스왑체인의 상태를 설명하는 구조체

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

		// 백버퍼의 갯수를 지정.
		scDesc.BufferCount = 1;

		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// 백버퍼의 용도와 접근권한을 지정함.
		// 여기서는 출력용 렌더타겟(그려질 곳)이라는 값임. 백버퍼에 직접 그림을 그리고 싶을때 사용함.
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		// 출력할 윈도우 핸들. 필수임.
		scDesc.OutputWindow = hwnd;

		// 멀티샘플링 매개변수를 지정함. 샘플수를 지정하는 Count와, 품질을 의미하는 Quality로 되어 있음.
		// MSAA를 끄려면 Count == 1, Quality == 0으로 지정되어야 함.
		// 주의 : 렌더타겟과 뎊스버퍼는 동일한 설정이어야만 함!


		scDesc.BufferDesc.Width = Application::GetInstance().GetWidth();
		scDesc.BufferDesc.Height = Application::GetInstance().GetHeight();
		scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		scDesc.SampleDesc.Count = 1;
		// 창모드일 경우, 윈도화면 전체가 전면버퍼가 되며, 
		// 전체화면 모드일 경우, 고유의 전면버퍼가 만들어짐.
		scDesc.Windowed = TRUE;


		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			NULL,                           // Dirext3D에서 사용할 그래픽카드 지정. NULL은 기본 그래픽카드를 사용한다는 의미
			D3D_DRIVER_TYPE_HARDWARE,       // 하드웨어 또는 소프트웨어 렌더링을 사용할 것인지를 지정.
			NULL,                           // HMODULE, 소프트 웨어 렌더링 구동기를 지정. 주로 DLL을 지정함.
			NULL,                           // Flags, Direct3D를 어떻게 실행할 것인지에 대한 플래그 지정.
			NULL,                           // D3D_FEATURE_LEVEL, 기능수준을 지정. Direct3D11을 사용할 경우에는 그냥 0을 넘겨주면 됨.
			NULL,                           // FeatureLevels 위에서 0을 주면, 여기도 0을 넘겨야함. 그러면 Direct3D11 기능수준을 사용함.(정확히는 D3D_FEATURE_LEVEL_11_0)
			D3D11_SDK_VERSION,              // 사용할 DirectX SDK 버전을 명시
			&scDesc,
			mcpSwapChain.ReleaseAndGetAddressOf(),
			mcpDevice.ReleaseAndGetAddressOf(),
			NULL,                           // 기능수준 배열을 반환함.
			mcpContext.ReleaseAndGetAddressOf()
		);
		ifFailed(hr);
		return false;
	}
	bool GraphicDevice_DX11::CreateRenderTargetAndDepthStencilBuffer()
	{
		HRESULT hr;
		// SwapChain <- back 그릴 예정 <- RenderTarget을 BackBuffer로 지정
		hr = mcpSwapChain->GetBuffer(
			0,                                                      // BackBuffer  
			IID_PPV_ARGS(mcpRenderTarget.ReleaseAndGetAddressOf())  // RenderTarget이 BackBuffer로.
		);
		ifFailed(hr);

		// Resource -> ResourceView로 연결
		mcpDevice->CreateRenderTargetView(
			mcpRenderTarget.Get(),
			nullptr,                                                // RENDER_TARGET_VIEW_DESC, NULL을 지정하면 밉맵 레벨 0의 모든 리로스에 접근 가능한 뷰가 생성됨.
			mcpRenderTargetView.GetAddressOf()
		);
		ifFailed(hr);

		// Depth-Stencil Buffer 만들기
		// C를 붙이면 마치 클래스인거 처럼 쓸 수 잇음.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,              // 4Byte니까, 앞에 3바이트를 depthBuffer로, 나머지 한 바이트는 Stencil로 씀.
			Application::GetInstance().GetWidth(),
			Application::GetInstance().GetHeight(),
			1,
			1,                                          // 1을 주면 한단계만 만드니까 원본만 사용함. 기본값은 2*2까지 만들어버림.
			D3D11_BIND_DEPTH_STENCIL                    // 텍스쳐를 어느 용도로 쓸래?
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

		// 렌더타겟과 뎊스-스텐실 버퍼를 바인딩함. 
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

		// 뷰포트 바인딩 (Rasterizer Stage -> RS)
		mcpContext->RSSetViewports(1, &viewPort);
	}

	void GraphicDevice_DX11::WriteConstantBufferAtGPU(ID3D11Buffer* pBuffer, void* pData, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;

		// 넘겨준 데이터를 매핑하여 매핑된 서브 리소스 구조체를 채워줌.
		// 성공하면 이 리소스에 GPU의 읽기가 금지 됨.
		HRESULT hr;
		hr = mcpContext->Map(
			pBuffer,							// 매핑할 리소스. 
			0,									// 서브리소스의 인덱스. 우리는 통째로 넘겨주므로 지정할 필요 없음
			D3D11_MAP_WRITE_DISCARD,			// 매핑방식을 지정. D3D11_MAP_WRITE_DISCARD 의미는 값을 쓰고 이전에 있던 값은 버리라는 의미.
			0,									// 추가 옵션으로 GPU가 바빠서 대기하고 있을 때, CPU의 작업을 지정한다. 현재는 DO_NOT_WAIT만 정의되어 있음. 우리는 GPU가 사용을 끝낼때 까지 기다린 후 버퍼에 값을 채워야 하니까 NULL을 주면 됨.
			&mappedSubResource					// 매핑된 리소스의 구조체를 돌려줌. 중요한것은 멤버 pData임. 여기에 리소스의 실제 데이터포인터가 void*로 들어있음.
		);
		ifFailed(hr);

		// 위 과정들을 거쳐 안전하게 값을 복사해도 되면 복사하게 됨.
		// 매핑된 서브리소스의 pData에 버텍스 구조체들을 메모리 복사하면 됨.
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

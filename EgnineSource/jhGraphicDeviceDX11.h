#pragma once
#include "jhGraphics.h"
#include "jhEnums.h"

namespace jh::graphics
{
	class GraphicDevice_DX11 final
	{
	public:
		GraphicDevice_DX11(eValidationMode mode);
		~GraphicDevice_DX11();

		bool CreateSwapChain(DXGI_SWAP_CHAIN_DESC* pSwapChainDesc);
		bool CreateSwapChain();
		bool CreateRenderTargetAndDepthStencilBuffer();
		bool CreateTexture(D3D11_TEXTURE2D_DESC* pTextureDesc, ID3D11Texture2D** ppTexture2D);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements, const void* pShaderByteInputSignature, SIZE_T byteCodeLength, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(D3D11_BUFFER_DESC* pBufferDesc, D3D11_SUBRESOURCE_DATA* pSubResourceData, ID3D11Buffer** ppBuffer);
		bool CreateAndSetShader();
		bool CreateVertexShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLincage, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader);
		void BindViewports(D3D11_VIEWPORT* pViewport);
		void BindViewports();
		void WriteConstantBufferAtGPU(ID3D11Buffer* pBuffer, void* pData, UINT size);
		void SetConstantBufferAtShader(eShaderStage shaderStage, eConstantBufferType eType, ID3D11Buffer* pBuffer);
		void SetVertexBufferAtIA(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* pBuffer, const UINT* pStride, const UINT* pOffeset);
		void SetIndexBufferAtIA(ID3D11Buffer* pIdxBufferm, DXGI_FORMAT format, UINT offset);
		void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void SetInputLayout(ID3D11InputLayout* pInputLayout);
		void SetVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances);
		void SetPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances);
		void Present();

		ID3D11DeviceContext* GetContext() const { return mcpContext.Get(); }
		ID3D11Device* GetID3D11Device() const { return mcpDevice.Get(); }
		void DrawIndexed(UINT idxCount, UINT startIdxLocation, UINT baseVertexLocation);


		__forceinline void ClearRenderTargetViewAndDepthStencilView()
		{
			FLOAT backGroundColor[4] = { 0.2f, 0.2f, 0.2f, 0.2f };
			mcpContext->ClearRenderTargetView(mcpRenderTargetView.Get(), backGroundColor);
			mcpContext->ClearDepthStencilView(
				mcpDepthStencilView.Get(),
				D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
				1.0f,
				0
			);
		}
	private:
		void ifFailed(HRESULT hr) { if (FAILED(hr)) { assert(false); } }
	private:
		Microsoft::WRL::ComPtr<ID3D11Device>				mcpDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>			mcpContext;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mcpRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mcpRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mcpDepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mcpDepthStencilView;

		Microsoft::WRL::ComPtr<IDXGISwapChain>				mcpSwapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState>			mcpSamplerState;
		D3D11_VIEWPORT mViewport;
	};
	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}

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
		bool CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);
		bool CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		bool CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppShaderResourceView);
		bool CreateAndSetShader();
		bool CreateVertexShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLincage, ID3D11VertexShader** ppVertexShader);
		bool CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader);
		bool CreatePixelShader(const void* pShaderByteCode, SIZE_T byteCodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader);
		bool CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		bool CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);
		bool CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState);


		void BindViewports(D3D11_VIEWPORT* pViewport);
		void BindViewports();
		void BindBufferAtGPU(ID3D11Buffer* pBuffer, void* pData, UINT size);
		
		void SetConstantBufferAtShader(const eShaderStage eStage, const eConstantBufferType eType, ID3D11Buffer* pBuffer);
		void SetVertexBufferAtIA(const UINT startSlot, const UINT numBuffers, ID3D11Buffer* const* pBuffer, const UINT* pStride, const UINT* pOffeset);
		void SetIndexBufferAtIA(ID3D11Buffer* pIdxBufferm, DXGI_FORMAT format, UINT offset);
		void SetPrimitiveTopologyAtIA(D3D11_PRIMITIVE_TOPOLOGY topology);
		void SetInputLayout(ID3D11InputLayout* pInputLayout);
		void SetVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances);
		void SetPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstance, UINT numClassInstances);
		void SetShaderResourceView(const eShaderStage eStage, const UINT slot, ID3D11ShaderResourceView* const* ppShaderResourceViews);
		void SetSamplersAtShader(const eShaderStage eStage, const UINT slot, const UINT numSamplers, ID3D11SamplerState* const* ppSamplerState);
		void SetSamplerAtALLShaders(const UINT slot, const UINT numSamplers, ID3D11SamplerState* const* ppSamplerState);
		void SetRasterizerState(ID3D11RasterizerState* pRasterizerState);
		void SetDepthStencilStateAtOM(ID3D11DepthStencilState* pDepthStencilState);
		void SetBlendStateAtOM(ID3D11BlendState* pBlendState);
		void Present();

		ID3D11DeviceContext* GetContext() const { return mcpContext.Get(); }
		ID3D11Device* GetID3D11Device() const { return mcpDevice.Get(); }
		void DrawIndexed(const UINT idxCount, const UINT startIdxLocation, const UINT baseVertexLocation);


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

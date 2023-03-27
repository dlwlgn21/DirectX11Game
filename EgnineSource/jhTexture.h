#pragma once
#include "jhResource.h"
#include "..\\External\\DirectXTex\\Include\\DirectXTex.h"
#include "jhGraphicDeviceDX11.h"


// TODO : 왜 이렇게 특이한 상대경로를 입력해주어야 할까요...???
#ifdef _DEBUG
#pragma comment(lib, "..\\..\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

//#ifdef _DEBUG
//#pragma comment(lib, "D:\\DirectX11Game\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
//#else
//#pragma comment(lib, "..\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib")
//#endif

namespace jh
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static void Clear(const UINT startSlot);
		HRESULT Load(const std::wstring& fileName) override;
		bool Create(const UINT width, const UINT height, const DXGI_FORMAT format, const UINT bindFlag);
		void SetShaderResourceView(const graphics::eShaderStage shaderStage, const UINT slot);
		void Clear();


		//void CreateUAV(const DXGI_FORMAT format);


		void SetUnorderdAccessView(const UINT startSlot);
		void ClearUnorderdAccessView(const UINT startSlot);

		UINT GetHeight() const { return static_cast<UINT>(mTextureDesc.Height); }
		UINT GetWidth() const { return static_cast<UINT>(mTextureDesc.Width); }

		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexture() const							{ return mcpTexture; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const			{ return mcpDepthStencilView; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const			{ return mcpRenderTargetView; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> GetUnorderedAccessView() const	{ return mcpUnorderedAccessView; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() const		{ return mcpShaderResourceView; }

	private:
		void createShaderResourceView();

	private:
		ScratchImage										mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mcpTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mcpShaderResourceView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mcpDepthStencilView;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mcpRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	mcpUnorderedAccessView;
		D3D11_TEXTURE2D_DESC								mTextureDesc;
	};
}


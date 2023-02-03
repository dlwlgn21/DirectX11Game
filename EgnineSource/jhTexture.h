#pragma once
#include "jhResource.h"
#include "..\\External\\DirectXTex\\Include\\DirectXTex.h"
#include "jhGraphicDeviceDX11.h"


// TODO : 왜 절대경로는 되고, 상대경로는 안 될까??
#ifdef _DEBUG
#pragma comment(lib, "D:\\DirectX11Game\\External\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "D:\\DirectX11Game\\External\\DirectXTex\\lib\\Release\\DirectXTex.lib")
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

		HRESULT Load(const std::wstring& fileName) override;
		void SetShaderResourceView(graphics::eShaderStage shaderStage, UINT slot);
	private:
		void createShaderResourceView();
	private:
		ScratchImage										mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mcpTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mcpShaderResourceView;
		D3D11_TEXTURE2D_DESC								mTextureDesc;
	};
}


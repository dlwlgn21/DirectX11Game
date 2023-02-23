#pragma once
#include "jhGraphics.h"
#include "jhResource.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	class Shader : public Resource
	{
	public:
		Shader();
		~Shader();

		HRESULT Load(const std::wstring& path) override;

		void SetPrimitiveTopologyAndIASetVertexAndPixelShader();
		void Create(graphics::eShaderStage eStage, const std::wstring& shaderFileName, const std::string& funcName);
		
		ID3D11InputLayout* GetInputLayout() const { return mcpInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return mcpInputLayout.GetAddressOf(); }

		void* GetVertexShaderBlob() { return mcpVertexShaderBlob->GetBufferPointer(); }
		SIZE_T GetVertexShaderBlobSize() { return mcpVertexShaderBlob->GetBufferSize(); }
		
		void SetRasterizerState(const graphics::eRasterizerStateType eType)		{ meRasterizerStateType = eType; }
		void SetDepthStencilState(const graphics::eDepthStencilStateType eType) { meDepthStencilStateType = eType; }
		void SetBlendState(const graphics::eBlendStateType eType)				{ meBlendStateType = eType; }
	private:
		__forceinline void setPrimitiveTopologyAndIA()
		{
			graphics::GetDevice()->SetPrimitiveTopologyAtIA(mPrimitiveTopology);
			graphics::GetDevice()->SetInputLayout(mcpInputLayout.Get());
		}

		__forceinline void setVertexAndPixelShader()
		{
			graphics::GetDevice()->SetVertexShader(mcpVertexShader.Get(), nullptr, 0);
			graphics::GetDevice()->SetPixelShader(mcpPixelShader.Get(), nullptr, 0);
		}


	private:
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpVertexShaderBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mcpVertexShader;

		Microsoft::WRL::ComPtr<ID3DBlob>				mcpPixelShaderBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mcpPixelShader;

		Microsoft::WRL::ComPtr<ID3D11HullShader>		mcpHullShader;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpHullShaderBlob;

		Microsoft::WRL::ComPtr<ID3D11DomainShader>		mcpDomainShader;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpDomainShaderBlob;

		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	mcpGeoShader;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpGeoShaderBlob;

		graphics::eRasterizerStateType					meRasterizerStateType;
		graphics::eDepthStencilStateType				meDepthStencilStateType;
		graphics::eBlendStateType						meBlendStateType;

		Microsoft::WRL::ComPtr<ID3DBlob>				mcpErrorBlob;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;

		D3D11_PRIMITIVE_TOPOLOGY						mPrimitiveTopology;
		graphics::eShaderStage							meShaderStage;
	};
}


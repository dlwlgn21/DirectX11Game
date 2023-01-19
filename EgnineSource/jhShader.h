#pragma once
#include "jhGraphics.h"
#include "jhResource.h"

namespace jh
{
	class Shader : public Resource
	{
	public:
		Shader();
		~Shader();

		HRESULT Load(const std::wstring& path) override;

		void Create(graphics::eShaderStage eStage, const std::wstring& shaderFileName, const std::string& funcName);
		void Binds();

		ID3D11InputLayout* GetInputLayout() const { return mcpInputLayout.Get(); }
		ID3D11InputLayout** GetInputLayoutAddressOf() { return mcpInputLayout.GetAddressOf(); }

		void* GetVertexShaderBlob() { return mcpVertexShaderBlob->GetBufferPointer(); }
		SIZE_T GetVertexShaderBufferSize() { return mcpVertexShaderBlob->GetBufferSize(); }

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



		Microsoft::WRL::ComPtr<ID3DBlob>				mcpErrorBlob;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;

		D3D11_PRIMITIVE_TOPOLOGY						mPrimitiveTopology;
		graphics::eShaderStage							meShaderStage;
	};
}


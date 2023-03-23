#include "jhShader.h"
#include "jhRenderer.h"

namespace jh
{
	Shader::Shader()
		: Resource(eResourceType::GRAPHIC_SHADER)
		, mcpVertexShaderBlob(nullptr)
		, mcpVertexShader(nullptr)
		, mcpPixelShaderBlob(nullptr)
		, mcpPixelShader(nullptr)
		, mcpHullShader(nullptr)
		, mcpHullShaderBlob(nullptr)
		, mcpDomainShader(nullptr)
		, mcpDomainShaderBlob(nullptr)
		, mcpGeoShader(nullptr)
		, mcpGeoShaderBlob(nullptr)
		, mcpErrorBlob(nullptr)
		, mcpInputLayout(nullptr)
		, meShaderStage()
		, mPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, meRasterizerStateType(eRasterizerStateType::SOLID_BACK)
		, meDepthStencilStateType(eDepthStencilStateType::LESS_FIRST)
		, meBlendStateType(eBlendStateType::ALPHA_BLEND)
	{

	}
	Shader::~Shader()
	{
		mcpVertexShaderBlob.Reset();
		mcpVertexShader.Reset();

		mcpPixelShaderBlob.Reset();
		mcpPixelShader.Reset();

		mcpHullShader.Reset();
		mcpHullShaderBlob.Reset();

		mcpDomainShader.Reset();
		mcpDomainShaderBlob.Reset();

		mcpGeoShader.Reset();
		mcpGeoShaderBlob.Reset();

		mcpErrorBlob.Reset();
		mcpInputLayout.Reset();
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return S_OK;
	}

	void Shader::SetPrimitiveTopologyAndIASetVertexAndPixelShader()
	{
		setPrimitiveTopologyAndIA();
		setVertexAndPixelShader();

		GetDevice()->SetRasterizerState(renderer::cpRasterizerStates[static_cast<UINT>(meRasterizerStateType)].Get());
		GetDevice()->SetDepthStencilStateAtOM(renderer::cpDepthStencilStates[static_cast<UINT>(meDepthStencilStateType)].Get());
		GetDevice()->SetBlendStateAtOM(renderer::cpBlendStates[static_cast<UINT>(meBlendStateType)].Get());
	}

	void Shader::Create(graphics::eShaderStage eStage, const std::wstring& shaderFileName, const std::string& entryFuncName)
	{
		// VertexShader 
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\SHADER_SOURCE\\";

		std::wstring vsPath(path.c_str());
		std::wstring psPath(path.c_str());
		HRESULT hr;

		switch (eStage)
		{
		case jh::graphics::eShaderStage::VERTEX_SHADER:
			vsPath += shaderFileName;
			hr = D3DCompileFromFile(
				vsPath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryFuncName.c_str(),
				"vs_5_0",
				0,
				0,
				mcpVertexShaderBlob.ReleaseAndGetAddressOf(),
				mcpErrorBlob.ReleaseAndGetAddressOf()
			);
			if (FAILED(hr))
			{
				OutputDebugStringA((char*)mcpErrorBlob->GetBufferPointer());
				mcpErrorBlob.Reset();
				assert(false);
			}

			graphics::GetDevice()->CreateVertexShader(
				mcpVertexShaderBlob->GetBufferPointer(),
				mcpVertexShaderBlob->GetBufferSize(),
				nullptr,
				mcpVertexShader.ReleaseAndGetAddressOf()
			);

			break;
		case jh::graphics::eShaderStage::PIXEL_SHADER:
			psPath += shaderFileName;

			hr = D3DCompileFromFile(
				psPath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				entryFuncName.c_str(),
				"ps_5_0",
				0,
				0,
				mcpPixelShaderBlob.ReleaseAndGetAddressOf(),
				mcpErrorBlob.ReleaseAndGetAddressOf()
			);

			if (FAILED(hr))
			{
				OutputDebugStringA((char*)mcpErrorBlob->GetBufferPointer());
				mcpErrorBlob.Reset();
				assert(false);
			}

			graphics::GetDevice()->CreatePixelShader(
				mcpPixelShaderBlob->GetBufferPointer(),
				mcpPixelShaderBlob->GetBufferSize(),
				nullptr,
				mcpPixelShader.ReleaseAndGetAddressOf()
			);
			break;
		default:
			assert(false);
			break;
		}
	}
}


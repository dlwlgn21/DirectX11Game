#include "jhComputeShader.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	ComputeShader::ComputeShader()
		: Resource(eResourceType::COMPUTE_SHADER)
		, mcpBlob(nullptr)
		, mcpComputeShader(nullptr)
		, mThreadGroupCountX(32)
		, mThreadGroupCountY(32)
		, mThreadGroupCountZ(1)
		, mThreadGroupX(0)
		, mThreadGroupY(0)
		, mThreadGroupZ(0)
	{
	}
	ComputeShader::~ComputeShader()
	{
		mcpComputeShader.Reset();
		mcpBlob.Reset();
	}
	HRESULT ComputeShader::Load(const std::wstring& path)
	{
		return S_OK;
	}
	bool ComputeShader::Create(const std::wstring& shaderFileName, const std::string& funcName)
	{
		Microsoft::WRL::ComPtr<ID3DBlob>			cpErrorBlob;
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\SHADER_SOURCE\\";
		std::wstring csPath(path.c_str());
		HRESULT hr;
		csPath += shaderFileName;
			hr = D3DCompileFromFile(
				csPath.c_str(),
				nullptr,
				D3D_COMPILE_STANDARD_FILE_INCLUDE,
				funcName.c_str(),
				"cs_5_0",
				0,
				0,
				mcpBlob.ReleaseAndGetAddressOf(),
				cpErrorBlob.ReleaseAndGetAddressOf()
			);
			if (FAILED(hr))
			{
				OutputDebugStringA((char*)cpErrorBlob->GetBufferPointer());
				cpErrorBlob.Reset();
				assert(false);
			}

			graphics::GetDevice()->CreateComputeShader(
				mcpBlob->GetBufferPointer(),
				mcpBlob->GetBufferSize(),
				nullptr,
				mcpComputeShader.ReleaseAndGetAddressOf()
			);
		return false;
	}
	void ComputeShader::OnExcute()
	{
		Bind();
		graphics::GetDevice()->SetComputeShader(mcpComputeShader.Get(), nullptr, 0);
		graphics::GetDevice()->Dispatch(mThreadGroupCountX, mThreadGroupCountY, mThreadGroupCountZ);
		Clear();
	}
	void ComputeShader::Bind()
	{
	}
	void ComputeShader::Clear()
	{
	}
}
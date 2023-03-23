#pragma once
#include "jhGraphics.h"
#include "jhResource.h"

namespace jh
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		virtual ~ComputeShader();

		HRESULT Load(const std::wstring& path) override;
		
		bool Create(const std::wstring& shaderFileName, const std::string& funcName);
		void OnExcute();

		virtual void Bind();
		virtual void Clear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob>			mcpBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mcpComputeShader;

		UINT										mThreadGroupCountX;
		UINT										mThreadGroupCountY;
		UINT										mThreadGroupCountZ;

		UINT										mThreadGroupX;
		UINT										mThreadGroupY;
		UINT										mThreadGroupZ;
	};

}


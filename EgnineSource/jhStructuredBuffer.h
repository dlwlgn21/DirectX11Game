#pragma once
#include "jhEntity.h"
#include "jhGraphics.h"


namespace jh::graphics
{
	class StructuredBuffer : public GPUBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();

		bool Create(UINT size, UINT stride, eShaderResourceViewType eSRVType, void* pData);
		void Bind(void* pData, UINT bufferSize);
		void SetShaderResourceView(eShaderStage eStage, UINT slot);

		UINT GetSize() const { return mSize; }
		UINT GetStride() const { return mStride; }
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mcpShaderResourceView;
		eShaderResourceViewType meShaderResourceViewType;

		UINT mSize;
		UINT mStride;
	};
}


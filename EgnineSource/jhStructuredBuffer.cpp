#include "jhStructuredBuffer.h"
#include "jhGraphicDeviceDX11.h"

namespace jh::graphics
{
	const UINT StructuredBuffer::TEXTURE_REGISTER_NUMBER = 13;
	StructuredBuffer::StructuredBuffer()
		: mcpShaderResourceView(nullptr)
		, meShaderResourceViewType(eShaderResourceViewType::NONE)
		, mSize(0)
		, mStride(0)
	{
	}
	StructuredBuffer::~StructuredBuffer()
	{
		//mcpShaderResourceView.Reset();
	}
	bool StructuredBuffer::Create(UINT size, UINT stride, eShaderResourceViewType eSRVType, void* pData)
	{
		meShaderResourceViewType = eSRVType;
		mSize = size;
		mStride = stride;

		BufferDesc.ByteWidth = mSize * mStride;
		BufferDesc.StructureByteStride = mSize;
		BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		if (pData != nullptr)
		{
			D3D11_SUBRESOURCE_DATA subResource = {};
			subResource.pSysMem = pData;
			if (!GetDevice()->CreateBuffer(&BufferDesc, &subResource, CpBuffer.GetAddressOf()))
			{
				assert(false);
				return false;
			}
		}
		else
		{
			if (!GetDevice()->CreateBuffer(&BufferDesc, nullptr, CpBuffer.GetAddressOf()))
			{
				assert(false);
				return false;
			}
		}
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;
		if (!GetDevice()->CreateShaderResourceView(CpBuffer.Get(), &srvDesc, mcpShaderResourceView.GetAddressOf()))
		{
			assert(false);
			return false;
		}
		return true;
	}
	void StructuredBuffer::BindBufferAtGPU(void* pData, UINT bufferSize)
	{
		if (mStride < bufferSize)
		{
			Create(mSize, bufferSize, meShaderResourceViewType, pData);
		}
		else
		{
			GetDevice()->BindBufferAtGPU(CpBuffer.Get(), pData, mSize * mStride);
		}
	}
	void StructuredBuffer::SetShaderResourceView(eShaderStage eStage, UINT slot)
	{
		GetDevice()->SetShaderResourceView(eStage, slot, mcpShaderResourceView.GetAddressOf());
	}
}
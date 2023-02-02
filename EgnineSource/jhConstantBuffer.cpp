#include "jhConstantBuffer.h"
#include "jhGraphicDeviceDX11.h"

using namespace jh::math;

namespace jh::graphics
{
	ConstantBuffer::ConstantBuffer(const eConstantBufferType eType)
		: meType(eType)
	{
	}
	ConstantBuffer::~ConstantBuffer()
	{
	}
	bool ConstantBuffer::CreateBuffer(UINT bufferSize)
	{
		ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
		ConstantBufferDesc.ByteWidth =				bufferSize;
		ConstantBufferDesc.Usage =					D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		ConstantBufferDesc.BindFlags =				D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDesc.CPUAccessFlags =			D3D11_CPU_ACCESS_WRITE;
		ConstantBufferDesc.MiscFlags =				0;
		ConstantBufferDesc.StructureByteStride =	0;

		if (!graphics::GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, CpBuffer.ReleaseAndGetAddressOf()))
		{
			return false;
		}
		return true;
	}
	void ConstantBuffer::WriteConstantBufferAtGPU(void* pData)
	{
		graphics::GetDevice()->WriteConstantBufferAtGPU(CpBuffer.Get(), pData, ConstantBufferDesc.ByteWidth);
	}
	void ConstantBuffer::SetConstantBufferAtShader(eShaderStage shaderStage)
	{
		graphics::GetDevice()->SetConstantBufferAtShader(shaderStage, meType, CpBuffer.Get());
	}
}
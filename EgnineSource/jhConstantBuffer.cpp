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
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth =				bufferSize;
		BufferDesc.Usage =					D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags =				D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.CPUAccessFlags =			D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags =				0;
		BufferDesc.StructureByteStride =	0;

		if (!graphics::GetDevice()->CreateBuffer(&BufferDesc, nullptr, CpBuffer.ReleaseAndGetAddressOf()))
		{
			return false;
		}
		return true;
	}
	void ConstantBuffer::WriteConstantBufferAtGPU(void* pData)
	{
		graphics::GetDevice()->BindBufferAtGPU(CpBuffer.Get(), pData, BufferDesc.ByteWidth);
	}
	void ConstantBuffer::SetConstantBufferAtShader(eShaderStage shaderStage)
	{
		graphics::GetDevice()->SetConstantBufferAtShader(shaderStage, meType, CpBuffer.Get());
	}
}
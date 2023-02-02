#pragma once
#include "jhGraphics.h"
#include "jhEnums.h"

namespace jh::graphics
{
	class ConstantBuffer final : GPUBuffer
	{
	public:
		ConstantBuffer(const eConstantBufferType eType);
		virtual ~ConstantBuffer();

		bool CreateBuffer(UINT bufferSize);
		void WriteConstantBufferAtGPU(void* data);
		void SetConstantBufferAtShader(eShaderStage shaderStage);

	private:
		const eConstantBufferType meType;
	};
}


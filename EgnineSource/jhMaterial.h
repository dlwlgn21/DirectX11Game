#pragma once
#include "jhResource.h"
#include "jhConstantBuffer.h"

using namespace jh::graphics;
namespace jh
{
	class Shader;
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		HRESULT Load(const std::wstring& path) override;

		void SetDataAtConstantBuffer(eGPUPrameterType eGPUParamType, void* pData);
		void WriteConstantBufferAtGPU();

		__forceinline void SetShader(Shader* pShader)	{ assert(pShader != nullptr); mpShader = pShader; }
		__forceinline Shader* GetShader() const			{ return mpShader; }

	private:
		Shader* mpShader;
		ConstantBuffer* mpConstantBuffer;
	};
}

